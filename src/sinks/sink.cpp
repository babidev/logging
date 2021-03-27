#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

sink::sink(const std::string& name, const logging::level level)
  : name_{name}, severity_level_{level}
{
}

std::string sink::name() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return name_;
}

void sink::set_severity_level(const logging::level level)
{
  std::lock_guard<std::mutex> lock(mutex_);
  severity_level_ = level;
}

}
}
