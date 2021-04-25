#ifndef LOGGING_FORMATTERS_FORMATTER_H
#define LOGGING_FORMATTERS_FORMATTER_H

#include <memory>
#include <string>

#include "logging/record.h"

namespace logging {
namespace formatters {

class formatter
{
public:
  virtual ~formatter() = default;
  virtual std::string format(const logging::record& record) = 0;
};

using formatter_ptr = std::shared_ptr<logging::formatters::formatter>;

}
}

#endif
