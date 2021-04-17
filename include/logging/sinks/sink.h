#ifndef LOGGING_SINKS_SINK_H
#define LOGGING_SINKS_SINK_H

#include <atomic>
#include <memory>
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
  virtual const std::string& name() const final;
  virtual logging::level level() const final;
  virtual void set_level(const logging::level level) final;
  virtual bool check_level(const logging::level level) const final;
  virtual void write(const logging::record& record) = 0;
protected:
  virtual std::string format(const logging::record& record);

  std::string name_;
  std::atomic<unsigned> level_;
};

using sink_ptr = std::shared_ptr<logging::sinks::sink>;

}
}
#endif
