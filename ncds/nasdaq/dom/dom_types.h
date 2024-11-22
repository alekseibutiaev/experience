#pragma once

#include <iosfwd>
#include <iomanip>
#include <variant>
#include <optional>

#include "../types.h"

namespace std {

  namespace details {

    template <std::size_t I, typename T0, typename ... Ts>
    std::enable_if_t<(I == 1U+sizeof...(Ts)), std::ostream &>
    streamV(std::ostream & s, std::variant<T0, Ts...> const &) {
      return s;
    }

    template <std::size_t I, typename T0, typename ... Ts>
    std::enable_if_t<(I < 1U+sizeof...(Ts)), std::ostream &>
    streamV (std::ostream & s, std::variant<T0, Ts...> const & v) {
      return I == v.index() ? s << std::get<I>(v) : streamV<I+1U>(s, v);
    }
  
  } /* namespace details */

  template<typename clk_t, typename drt_t>
  std::ostream& operator<<(std::ostream& os, const std::chrono::time_point<clk_t, drt_t>& v) {
    const time_t t_c = clk_t::to_time_t(v);
  #if __GNUC__ > 4 || \
      ((__GNUC__ == 4) && __GNUC_MINOR__ > 8 && __GNUC_REVISION__ > 1)
    // Maybe the put_time will be implemented later?
    return os << std::put_time(std::localtime(&t_c), "%F %T") << '.' << std::setfill('0') <<
      std::setw(3) << std::chrono::time_point_cast<std::chrono::milliseconds>(v).time_since_epoch().count() % 1000;
  #else
    char buffer[26];
    ctime_r(&t_c, buffer);
    buffer[24] = '\0';  // Removes the newline that is added
    return os << buffer;
  #endif
  }


  template <typename T0, typename ... Ts>
  std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) {
    return details::streamV<0U>(s, v);
  }

} /*namespace std*/

namespace nasdaq {

namespace dom {

    enum value_types {
      e_boolean,
      e_bytes,
      e_int,
      e_long,
      e_double,
      e_time_point,
      e_string,
      e_count
    };

    using value_t = std::variant<bool, unsigned char, int, long, double, time_point_t, std::string>;

  } /* namespace dom */

} /* namespace nasdaq */
