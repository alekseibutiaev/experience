#include <cctype>
#include <cstdio>

#include <iomanip>
#include <iostream>

#include "hexbuf.hpp"

namespace tools {

  hexbuf_t::hexbuf_t(const unsigned char* buf, std::size_t size)
      : m_buf(buf)
      , m_size(size) {
  }

  std::ostream& operator<<(std::ostream& os, const hexbuf_t& value) {
    const std::size_t line_size = 16;
    char hex[line_size * 3 + 1] = { 0 };
    char sym[line_size + 1] = { 0 };
    char* hexp = hex; 
    char* symp = sym;
    os << std::endl;
    for(std::size_t i = 0; i < value.m_size; ) {
      const int v = static_cast<int>(value.m_buf[i]);
      hexp += sprintf(hexp, "%02X ", v);
      symp += sprintf(symp, "%c", std::isprint(v) ? static_cast<char>(v) : '.' );
      ++i;
      if(0 != i % line_size)
        continue;
      os << hex << ' ' << sym << std::endl;
      hexp = hex;
      symp = sym;
    }
    if(value.m_size % line_size)
      os << std::left << std::setfill(' ') << std::setw(line_size * 3) << hex
        << ' ' << std::setw(line_size) << sym << std::endl;
    return os;
  }

} /* namespace tools */
