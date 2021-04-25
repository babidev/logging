#ifndef LOGGING_SINKS_FILE_H
#define LOGGING_SINKS_FILE_H

#include <fstream>

#include "logging/sinks/sink.h"

namespace logging {
namespace sinks {

class file final : public sink
{
public:
  file(const std::string& name, logging::formatters::formatter_ptr formatter,
    const logging::level level, const std::string& filename);
  ~file();
  void write(const logging::record& record) override;
private:
  std::ofstream output_;
};

}
}
#endif
