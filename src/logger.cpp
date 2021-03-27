#include "logging/logger.h"

#include <utility>

namespace logging {

std::atomic<logger*> logger::instance_;
std::mutex logger::instance_guard_;

logger::logger()
{
  running_.store(false, std::memory_order_relaxed);
}

logger::~logger()
{
  stop();
}

logger& logger::instance()
{
  logger* ptr = instance_.load(std::memory_order_acquire);
  if (!ptr) {
    std::lock_guard<std::mutex> lock(instance_guard_);
    ptr = instance_.load(std::memory_order_relaxed);
    if (!ptr) {
      ptr = new logger();
      instance_.store(ptr, std::memory_order_release);
    }
  }
  return *ptr;
}

void logger::destroy()
{
  std::lock_guard<std::mutex> lock(instance_guard_);
  logger* ptr = instance_.load(std::memory_order_acquire);
  if (ptr) {
    delete ptr;
    instance_.store(nullptr, std::memory_order_release);
  }
}

void logger::start()
{
  if (!running_.load(std::memory_order_acquire)) {
    running_.store(true, std::memory_order_release);
    dispatcher_ = std::move(std::thread([this]() { dispatch(); }));
  }
}

void logger::stop()
{
  if (running_.load(std::memory_order_acquire)) {
    running_.store(false, std::memory_order_release);
    {
      std::lock_guard<std::mutex> lock(mutex_);
      write_condition_.notify_one();
    }
    if (dispatcher_.joinable()) {
      dispatcher_.join();
    }
  }
}

void logger::write(const std::string& sink_name, const logging::level level, const std::string& message) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!sinks_.empty()) {
    auto it = sinks_.find(sink_name);
    if (it != sinks_.end()) {
      logs_.emplace(std::make_tuple(it->second, level, message));
      write_condition_.notify_one();
    }
  }
}

void logger::register_sink(logging::sinks::sink_ptr sink)
{
  std::lock_guard<std::mutex> lock(mutex_);
  sinks_.emplace(sink->name(), sink);
}

void logger::deregister_sink(logging::sinks::sink_ptr sink)
{
  if (sink != nullptr) {
    std::string sink_name{sink->name()};
    std::lock_guard<std::mutex> lock(mutex_);
    sinks_.erase(sink_name);
  }
}

void logger::deregister_sink(const std::string& sink_name)
{
  std::lock_guard<std::mutex> lock(mutex_);
  sinks_.erase(sink_name);
}

void logger::dispatch()
{
  while(running_.load(std::memory_order_acquire)) {
    std::queue<std::tuple<logging::sinks::sink_ptr,logging::level,std::string>> buffer;
    {
      std::unique_lock<std::mutex> lock(mutex_);
      if (logs_.empty()) {
        write_condition_.wait(lock);
      }
      std::swap(logs_, buffer);
    }
    while(!buffer.empty()) {
      auto log = buffer.front();
      buffer.pop();
      std::get<0>(log)->write(std::get<1>(log), std::get<2>(log));
    }
  }
}

}