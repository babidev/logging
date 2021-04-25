#ifndef LOGGING_SINKS_CERR_H
#define LOGGING_SINKS_CERR_H

#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

class cerr final : public sink
{
public:
  cerr(const std::string& name, logging::formatters::formatter_ptr formatter,
    const logging::level level);
  void write(const logging::record& record) override;
};

}
}
#endif
