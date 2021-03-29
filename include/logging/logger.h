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
#include "logging/record.h"
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
  void handle(const std::string& sink_name, const logging::record& record);
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
  std::queue<std::tuple<logging::sinks::sink_ptr,logging::record>> records_;
  std::unordered_map<std::string,logging::sinks::sink_ptr> sinks_;
};

}
#endif
