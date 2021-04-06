#include "logging/sinks/cerr.h"

#include <iostream>
#include <sstream>

namespace logging {
namespace sinks {

cerr::cerr(const std::string& name, const logging::level level)
  : sink(name, level)
{
}

void cerr::write(const logging::record& record)
{
  auto duration = std::chrono::time_point_cast<std::chrono::nanoseconds>(
                  std::chrono::system_clock::now()).time_since_epoch().count()
                - std::chrono::time_point_cast<std::chrono::nanoseconds>(
                  record.time_point).time_since_epoch().count();

  std::ostringstream stream;
  stream << "[THREAD-ID:" << record.thread_id << "]"
         << "[" << std::fixed << 0.000001 * duration << "ms]"
         << "[" << logging::level_to_string(record.level) << "]"
         << " " << record.message << std::endl;

  std::cerr << stream.str();
}

}
}
