#include "logging/log.h"

#include "logging/logger.h"
#include "logging/record.h"

namespace logging {

log::log(const std::string& sink_name, const logging::level level)
  : sink_name_{sink_name}, level_{level}
{
}

log::~log()
{
  logger::instance().handle(sink_name_, logging::record{ stream_.str(),
      level_, std::this_thread::get_id(), std::chrono::system_clock::now() });
}

}
