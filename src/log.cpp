#include "logging/log.h"

#include "logging/logger.h"

namespace logging {

log::log(const std::string& sink_name, const logging::level level)
  : sink_name_{sink_name}, level_{level}
{
}

log::~log()
{
  logger::instance().write(sink_name_, level_, stream_.str());
}

}
