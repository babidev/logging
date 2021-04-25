#include "logging/sinks/cout.h"

#include <iostream>

namespace logging {
namespace sinks {

cout::cout(const std::string& name, logging::formatters::formatter_ptr formatter,
    const logging::level level)
  : sink(name, formatter, level)
{
}

void cout::write(const logging::record& record)
{
  if (formatter_) {
    std::cout << formatter_->format(record);
  }
}

}
}
