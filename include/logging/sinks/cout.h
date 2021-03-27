#ifndef LOGGING_SINKS_COUT_H
#define LOGGING_SINKS_COUT_H

#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

class cout final : public sink
{
public:
  cout(const std::string& name, const logging::level level);
  void write(const logging::level level, const std::string& message) override;
};

}
}
#endif
