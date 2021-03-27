#ifndef LOGGING_LOG_H
#define LOGGING_LOG_H

#include <sstream>
#include <string>

#include "logging/level.h"

namespace logging {

class log
{
public:
  log(const std::string& sink_name, const logging::level level);
  virtual ~log();

  template<typename T>
  log& operator<<(const T& value) {
    stream_ << value;
    return *this;
  }
private:
  log(const log&) = delete;
  log& operator=(const log&) = delete;

  std::string sink_name_;
  logging::level level_;
  std::ostringstream stream_;
};

#define debug(sink)    log(sink, logging::level::debug)
#define info(sink)     log(sink, logging::level::info)
#define warning(sink)  log(sink, logging::level::warning)
#define error(sink)    log(sink, logging::level::error)
#define critical(sink) log(sink, logging::level::critical)

}
#endif
