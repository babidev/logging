#include "logging/manager.h"

#include <utility>

namespace logging {

std::atomic<manager*> manager::instance_;

manager::manager()
{
  state_.store(0, std::memory_order_relaxed);
}

manager::~manager()
{
  stop();
}

manager& manager::instance()
{
  manager* instance = instance_.load(std::memory_order_acquire);
  if (instance == nullptr) {
    manager* ptr = new manager();
    if (!instance_.compare_exchange_strong(instance, ptr,
      std::memory_order_release, std::memory_order_relaxed)) {
      delete ptr;
    } else {
      return *ptr;
    }
  }
  return *instance;
}

void manager::destroy()
{
  manager* instance = instance_.load(std::memory_order_acquire);
  if (instance != nullptr) {
    manager* ptr = nullptr;
    if (instance_.compare_exchange_strong(instance, ptr,
      std::memory_order_release, std::memory_order_relaxed)) {
      delete instance;
    }
  }
}

void manager::start()
{
  unsigned state = state_.load(std::memory_order_acquire);
  if (state == 2 || state == 3) {
    return;
  }
  while (state == 1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    state = state_.load(std::memory_order_acquire);
  }
  if (state == 0) {
    if (state_.compare_exchange_strong(state, 2, std::memory_order_relaxed)) {
       dispatcher_ = std::move(std::thread([this]() { dispatch(); }));
       state_.store(3, std::memory_order_release);
    }
  }
}

void manager::stop()
{
  unsigned state = state_.load(std::memory_order_acquire);
  if (state == 1 || state == 0) {
    return;
  }
  while (state == 2) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    state = state_.load(std::memory_order_acquire);
  }
  if (state == 3) {
    if (state_.compare_exchange_strong(state, 1, std::memory_order_relaxed)) {
      write_condition_.notify_one();
      if (dispatcher_.joinable()) {
        dispatcher_.join();
      }
      state_.store(0, std::memory_order_release);
    }
  }
}

void manager::handle(const std::string& sink_name, const logging::record& record) {
  if (state_.load(std::memory_order_acquire) < 2) {
    return;
  }
  std::unique_lock<std::mutex> lock(mutex_);
  if (!sinks_.empty()) {
    auto search = sinks_.find(sink_name);
    if (search != sinks_.end()) {
      if (search->second->check_level(record.level)) {
        records_.emplace(std::make_tuple(search->second, record));
        lock.unlock();
        write_condition_.notify_one();
      }
    }
  }
}

void manager::register_sink(logging::sinks::sink_ptr sink)
{
  std::lock_guard<std::mutex> lock(mutex_);
  sinks_.emplace(sink->name(), sink);
}

void manager::deregister_sink(logging::sinks::sink_ptr sink)
{
  if (sink != nullptr) {
    std::lock_guard<std::mutex> lock(mutex_);
    sinks_.erase(sink->name());
  }
}

void manager::deregister_sink(const std::string& sink_name)
{
  std::lock_guard<std::mutex> lock(mutex_);
  sinks_.erase(sink_name);
}

logging::sinks::sink_ptr manager::get_sink(const std::string& sink_name)
{
  std::lock_guard<std::mutex> lock(mutex_);
  if (!sinks_.empty()) {
    auto search = sinks_.find(sink_name);
    if (search != sinks_.end()) {
      return search->second;
    }
  }
  return nullptr;
}

void manager::dispatch()
{
  bool is_records_queue_empty = true;
  while(state_.load(std::memory_order_acquire) > 1 || !is_records_queue_empty) {
    std::queue<std::tuple<logging::sinks::sink_ptr,logging::record>> buffer;
    std::unique_lock<std::mutex> lock(mutex_);
    if (records_.empty()) {
      write_condition_.wait(lock);
    }
    std::swap(records_, buffer);
    lock.unlock();
    while(!buffer.empty()) {
      auto item = buffer.front();
      std::get<0>(item)->write(std::get<1>(item));
      buffer.pop();
    }
    lock.lock();
    is_records_queue_empty = records_.empty();
  }
}

}
