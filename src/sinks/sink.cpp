#include "logging/sinks/sink.h"

#include <sstream>

namespace logging {
namespace sinks {

sink::sink(const std::string& name, const logging::level level)
  : name_{name}
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

std::string sink::format(const logging::record& record)
{
  auto duration = std::chrono::time_point_cast<std::chrono::nanoseconds>(
                  std::chrono::system_clock::now()).time_since_epoch().count()
                - std::chrono::time_point_cast<std::chrono::nanoseconds>(
                  record.time_point).time_since_epoch().count();

  std::ostringstream stream;
  stream << "[THREAD-ID:" << record.thread_id << "]"
         << "[" << std::fixed << 0.000001 * duration << "ms]"
         << "[" << logging::level_to_string(record.level) << "]"
         << " " << record.message << "\n";

  return stream.str();
}

}
}
