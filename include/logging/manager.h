#ifndef LOGGING_MANAGER_H
#define LOGGING_MANAGER_H

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "logging/level.h"
#include "logging/sinks/sink.h"

namespace logging {

class manager final
{
public:
  static manager& instance();
  static void destroy();
  void register_sink(logging::sinks::sink_ptr sink);
  void deregister_sink(logging::sinks::sink_ptr sink);
  void deregister_sink(const std::string& sink_name);
  logging::sinks::sink_ptr get_sink(const std::string& sink_name);
private:
  manager() = default;
  manager(const manager&) = delete;
  manager& operator=(const manager&) = delete;

  static std::atomic<manager*> instance_;
  std::mutex mutex_;
  std::unordered_map<std::string,logging::sinks::sink_ptr> sinks_;
};

}
#endif
