#include "logging/sinks/cerr.h"

#include <iostream>

namespace logging {
namespace sinks {

cerr::cerr(const std::string& name, logging::formatters::formatter_ptr formatter,
  const logging::level level)
  : sink(name, formatter, level)
{
}

void cerr::write(const logging::record& record)
{
  if (formatter_) {
    std::cerr << formatter_->format(record);
  }
}

}
}
