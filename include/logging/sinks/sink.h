#ifndef LOGGING_SINKS_SINK_H
#define LOGGING_SINKS_SINK_H

#include <memory>
#include <mutex>
#include <string>

#include "logging/level.h"
#include "logging/record.h"

namespace logging {
namespace sinks {

class sink
{
public:
  sink(const std::string& name, const logging::level level);
  virtual ~sink() = default;
  virtual std::string name() const final;
  virtual logging::level level() const final;
  virtual void set_level(const logging::level level) final;
  virtual bool check_level(const logging::level level) const final;
  virtual void write(const logging::record& record) = 0;
protected:
  std::string name_;
  logging::level level_;
  mutable std::mutex mutex_;
};

using sink_ptr = std::shared_ptr<logging::sinks::sink>;

}
}
#endif
