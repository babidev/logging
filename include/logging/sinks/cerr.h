#ifndef LOGGING_SINKS_CERR_H
#define LOGGING_SINKS_CERR_H

#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

class cerr final : public sink
{
public:
  cerr(const std::string& name, const logging::level level);
  void write(const logging::level level, const std::string& message) override;
};

}
}
#endif
