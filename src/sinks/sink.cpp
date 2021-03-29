#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

sink::sink(const std::string& name, const logging::level level)
  : name_{name}, level_{level}
{
}

std::string sink::name() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return name_;
}

logging::level sink::level() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return level_;
}

void sink::set_level(const logging::level level)
{
  std::lock_guard<std::mutex> lock(mutex_);
  level_ = level;
}

bool sink::check_level(const logging::level level) const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return level_ != logging::level::none && level_ <= level;
}

}
}
