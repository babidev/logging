#include "logging/manager.h"

namespace logging {

std::atomic<manager*> manager::instance_;

manager& manager::instance()
{
  manager* instance = instance_.load(std::memory_order_acquire);
  if (!instance) {
    manager* ptr = new manager();
    if (!instance_.compare_exchange_strong(instance, ptr,
      std::memory_order_release, std::memory_order_relaxed)) {
      delete ptr;
    }
  }
  return *instance_.load(std::memory_order_relaxed);
}

void manager::destroy()
{
  manager* instance = instance_.load(std::memory_order_acquire);
  if (instance) {
    manager* ptr = nullptr;
    if (instance_.compare_exchange_strong(instance, ptr,
      std::memory_order_release, std::memory_order_relaxed)) {
      delete instance;
    }
  }
}

void manager::register_sink(logging::sinks::sink_ptr sink)
{
  std::lock_guard lock(mutex_);
  sinks_.emplace(sink->name(), sink);
}

void manager::deregister_sink(logging::sinks::sink_ptr sink)
{
  if (sink != nullptr) {
    std::lock_guard lock(mutex_);
    sinks_.erase(sink->name());
  }
}

void manager::deregister_sink(const std::string& sink_name)
{
  std::lock_guard lock(mutex_);
  sinks_.erase(sink_name);
}

logging::sinks::sink_ptr manager::get_sink(const std::string& sink_name)
{
  std::shared_lock lock(mutex_);
  if (!sinks_.empty()) {
    auto search = sinks_.find(sink_name);
    if (search != sinks_.end()) {
      return search->second;
    }
  }
  return nullptr;
}

}
