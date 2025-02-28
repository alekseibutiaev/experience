#include <iomanip>
#include <sstream>

#include "tools.h"

namespace nasdaq {

  std::string time_print(const clock_t::time_point now) {
    static const char* format[] = {"%H:%M:%S", "%Y%m%d %H:%M:%S"};
    const auto frac = (std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % std::chrono::seconds(1)).count();
    const auto _now = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    std::ostringstream oss;
    std::tm time;
    localtime_r(&_now, &time);
    oss << std::put_time(&time, format[86400 < _now]) << '.'<< std::left <<
      std::setw(6) << std::setfill('0') << frac;
    return oss.str();
  }

} /* namespace nasdaq */
