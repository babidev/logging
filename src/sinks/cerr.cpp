#include "logging/sinks/cerr.h"

#include <iostream>

namespace logging {
namespace sinks {

cerr::cerr(const std::string& name, const logging::level level)
  : sink(name, level)
{
}

void cerr::write(const logging::record& record)
{
  std::cerr << format(record);
}

}
}
