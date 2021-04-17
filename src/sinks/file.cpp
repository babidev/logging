#include "logging/sinks/file.h"

namespace logging {
namespace sinks {

file::file(const std::string& name, const logging::level level, const std::string& filename)
  : sink(name, level)
{
  output_.open(filename);
}

file::~file()
{
  output_.close();
}

void file::write(const logging::record& record)
{
  if (output_.is_open()) {
    output_ << format(record);
    output_.flush();
  }
}

}
}
