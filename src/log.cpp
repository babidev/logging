#include "logging/log.h"

#include "logging/manager.h"
#include "logging/record.h"

namespace logging {

log::log(const std::string& sink_name, const logging::level level)
  : sink_name_{sink_name}, level_{level}
{
}

log::~log()
{
  logging::sinks::sink_ptr sink = logging::manager::instance().get_sink(sink_name_);
  if (sink) {
    if (sink->check_level(level_)) {
      sink->write(logging::record{ stream_.str(), level_,
        std::this_thread::get_id(), std::chrono::system_clock::now() });
    }
  }
}

}
