#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

sink::sink(const std::string& name, logging::formatters::formatter_ptr formatter,
  const logging::level level)
  : name_{name}, formatter_{formatter}
{
  level_.store(static_cast<unsigned>(level), std::memory_order_relaxed);
}

const std::string& sink::name() const
{
  return name_;
}

logging::level sink::level() const
{
  return static_cast<logging::level>(level_.load(std::memory_order_acquire));
}

void sink::set_level(const logging::level level)
{
  level_.store(static_cast<unsigned>(level), std::memory_order_release);
}

bool sink::check_level(const logging::level level) const
{
  unsigned current = level_.load(std::memory_order_acquire);
  return current != static_cast<unsigned>(logging::level::none) &&
         current <= static_cast<unsigned>(level);
}

}
}
