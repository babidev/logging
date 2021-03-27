#ifndef LOGGING_SINKS_SINK_H
#define LOGGING_SINKS_SINK_H

#include <memory>
#include <mutex>
#include <string>

#include "logging/level.h"

namespace logging {
namespace sinks {

class sink
{
public:
  sink(const std::string& name, const logging::level level);
  virtual ~sink() = default;
  virtual std::string name() const final;
  virtual void set_severity_level(const logging::level level) final;
  virtual void write(const logging::level level, const std::string& message) = 0;
protected:
  std::string name_;
  logging::level severity_level_;
  mutable std::mutex mutex_;
};

using sink_ptr = std::shared_ptr<logging::sinks::sink>;

}
}
#endif
