#include "logging/sinks/cerr.h"

#include <iostream>

namespace logging {
namespace sinks {

cerr::cerr(const std::string& name, const logging::level level)
  : sink(name, level)
{
}

void cerr::write(const logging::level level, const std::string& message)
{
  std::lock_guard<std::mutex> lock(mutex_);
  if (severity_level_ != logging::level::none && severity_level_ <= level) {
    std::cerr << logging::level_to_string(level) << " | "
              << name_ << " | "
              << message << std::endl;
  }
}

}
}
