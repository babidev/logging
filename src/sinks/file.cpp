#include "logging/sinks/file.h"

namespace logging {
namespace sinks {

file::file(const std::string& name, logging::formatters::formatter_ptr formatter,
    const logging::level level, const std::string& filename)
  : sink(name, formatter, level)
{
  output_.open(filename);
}

file::~file()
{
  output_.close();
}

void file::write(const logging::record& record)
{
  if (formatter_ && output_.is_open()) {
    output_ << formatter_->format(record);
    output_.flush();
  }
}

}
}
