#include "logging/level.h"

#include <unordered_map>

const std::unordered_map<logging::level, std::string> level_string_map {
  {logging::level::debug   , "DEBUG"},
  {logging::level::info    , "INFO"},
  {logging::level::warning , "WARNING"},
  {logging::level::error   , "ERROR"},
  {logging::level::critical, "CRITICAL"}
};

std::string logging::level_to_string(const logging::level level) {
  auto search = level_string_map.find(level);
  if (search != level_string_map.end()) {
    return search->second;
  }
  return std::string{"NONE"};
}
