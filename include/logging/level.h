#ifndef LOGGING_LEVEL_H
#define LOGGING_LEVEL_H

#include <string>

namespace logging {

enum class level
{
  none     = 0,
  debug    = 1,
  info     = 2,
  warning  = 3,
  error    = 4,
  critical = 5
};

std::string level_to_string(const logging::level level);

}
#endif
