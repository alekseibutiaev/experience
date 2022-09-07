#include <cstddef>
#include <type_traits>
#include <limits>

namespace kh {

  template<typename type_t>
  type_t to_gray(type_t value, typename std::enable_if<std::is_unsigned<type_t>::value>::type* = 0) {
    return value ^ (value >> 1);
  }

  template<typename type_t>
  type_t from_gray(type_t value, typename std::enable_if<std::is_unsigned<type_t>::value>::type* = 0) {
    auto mask = std::numeric_limits<type_t>::digits >> 1;
    while(mask) {
      value ^= value >> mask;
      mask >>= 1;
    }
    return value;
  }

} /* namespace kh */
