#include "logging/sinks/cout.h"

#include <iostream>

namespace logging {
namespace sinks {

cout::cout(const std::string& name, const logging::level level)
  : sink(name, level)
{
}

void cout::write(const logging::record& record)
{
  std::cout << format(record);
}

}
}
