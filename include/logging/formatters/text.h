#ifndef LOGGING_FORMATTERS_TEXT_H
#define LOGGING_FORMATTERS_TEXT_H

#include "logging/formatters/formatter.h"

namespace logging {
namespace formatters {

class text final : public formatter
{
public:
  std::string format(const logging::record& record) override;
};

}
}

#endif
