#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

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
#include "logging/sinks/sink.h"

namespace logging {

class logger final
{
public:
  ~logger();
  static logger& instance();
  static void destroy();
  void start();
  void stop();
  void write(const std::string& sink_name, const logging::level level, const std::string& message);
  void register_sink(logging::sinks::sink_ptr sink);
  void deregister_sink(logging::sinks::sink_ptr sink);
  void deregister_sink(const std::string& sink_name);
private:
  logger();
  logger(const logger&) = delete;
  logger& operator=(const logger&) = delete;
  void dispatch();

  static std::atomic<logger*> instance_;
  static std::mutex instance_guard_;

  std::atomic<bool> running_;
  std::thread dispatcher_;
  std::mutex mutex_;
  std::condition_variable write_condition_;
  std::queue<std::tuple<logging::sinks::sink_ptr,logging::level,std::string>> logs_;
  std::unordered_map<std::string,logging::sinks::sink_ptr> sinks_;
};

}
#endif
