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
  std::cerr << "[" << logging::level_to_string(level) << "]"
            << " " << message << std::endl;
}

}
}
