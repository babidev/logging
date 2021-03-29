#ifndef LOGGING_RECORD_H
#define LOGGING_RECORD_H

#include <chrono>
#include <string>
#include <thread>

#include "logging/level.h"

namespace logging {

struct record
{
  std::string message;
  logging::level level;
  std::thread::id thread_id;
  std::chrono::system_clock::time_point time_point;
};

}
#endif
