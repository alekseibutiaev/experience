#include <chrono>


#include "tools.hpp"

#include "timeformat.hpp"

namespace tools {

  std::string time_milliseconds() {
    char buf[64] = {0};
    const auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    const auto sec = now / 1000;
    const std::size_t pos = strftime(buf, std::size(buf), "%F %T", std::localtime(&sec));
    snprintf(buf + pos, std::size(buf) - pos, ".%03ld", now % 1000);
    return std::string(buf);
  }

  std::string time_seconds() {
    char buf[64] = {0};
    const auto sec = std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
    buf[strftime(buf, std::size(buf), "%F %T", std::localtime(&sec))] = 0;
    return std::string(buf);
  }

} /* namespace tools */