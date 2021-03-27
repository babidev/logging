#include "logging/sinks/cout.h"

#include <iostream>

namespace logging {
namespace sinks {

cout::cout(const std::string& name, const logging::level level)
  : sink(name, level)
{
}

void cout::write(const logging::level level, const std::string& message)
{
  std::lock_guard<std::mutex> lock(mutex_);
  if (severity_level_ != logging::level::none && severity_level_ <= level) {
    std::cout << logging::level_to_string(level) << " | "
              << name_ << " | "
              << message << std::endl;
  }
}

}
}
