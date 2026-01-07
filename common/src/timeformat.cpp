#include <chrono>


#include "tools.hpp"

#include "timeformat.hpp"

namespace {

  std::string time_format(const std::string& format, std::time_t time) {
    char buf[64] = {0};
    if(0 == time)
      time = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    buf[strftime(buf, std::size(buf), format.c_str(), std::localtime(&time))] = 0;
    return std::string(buf);
  }

} /* namespace */

namespace tools {

  std::string time_milliseconds(long long time) {
    char buf[64] = {0};
    if(0 == time)
      time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    const std::time_t sec = time / 1000;
    const std::size_t pos = strftime(buf, std::size(buf), "%Y%m%d-%H:%M:%S", std::localtime(&sec));
    snprintf(buf + pos, std::size(buf) - pos, ".%03lld", time % 1000);
    return std::string(buf);
  }

  std::string time_seconds(std::time_t time) {
    return time_format("%Y%m%d-%H%M%S", time);
  }

  std::string time_minute(std::time_t time) {
    return time_format("%Y%m%d-%H%M", time);
  }

  std::string time_hour(std::time_t time) {
    return time_format("%Y%m%d-%H", time);
  }

} /* namespace tools */