#ifndef LOGGING_SINKS_COUT_H
#define LOGGING_SINKS_COUT_H

#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

class cout final : public sink
{
public:
  cout(const std::string& name, logging::formatters::formatter_ptr formatter,
    const logging::level level);
  void write(const logging::record& record) override;
};

}
}
#endif
