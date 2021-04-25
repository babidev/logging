#include "logging/formatters/text.h"

#include <sstream>

namespace logging {
namespace formatters {

std::string text::format(const logging::record& record)
{
  std::ostringstream stream;
  stream << "[THREAD-ID:" << record.thread_id << "]"
         << "[" << logging::level_to_string(record.level) << "]"
         << " " << record.message << "\n";

  return stream.str();
}

}
}
