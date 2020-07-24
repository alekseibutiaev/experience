#pragma once

#include <ctime>
#include <string>

namespace tools {

  std::string time_milliseconds(long long time = 0);
  std::string time_seconds(std::time_t time = 0);
  std::string time_minute(std::time_t time = 0);
  std::string time_hour(std::time_t time = 0);

} /* namespace tools */
