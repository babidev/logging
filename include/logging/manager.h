#ifndef LOGGING_MANAGER_H
#define LOGGING_MANAGER_H

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>

#include "logging/level.h"
#include "logging/record.h"
#include "logging/sinks/sink.h"

namespace logging {

class manager final
{
public:
  ~manager();
  static manager& instance();
  static void destroy();
  void start();
  void stop();
  void handle(const std::string& sink_name, const logging::record& record);
  void register_sink(logging::sinks::sink_ptr sink);
  void deregister_sink(logging::sinks::sink_ptr sink);
  void deregister_sink(const std::string& sink_name);
  logging::sinks::sink_ptr get_sink(const std::string& sink_name);
private:
  manager();
  manager(const manager&) = delete;
  manager& operator=(const manager&) = delete;
  void dispatch();

  static std::atomic<manager*> instance_;
  std::atomic<unsigned> state_; //0=off, 1=stopping, 2=starting, 3=on
  std::thread dispatcher_;
  std::mutex mutex_;
  std::condition_variable write_condition_;
  std::queue<std::tuple<logging::sinks::sink_ptr,logging::record>> records_;
  std::unordered_map<std::string,logging::sinks::sink_ptr> sinks_;
};

}
#endif