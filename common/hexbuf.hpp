#pragma once

#include <iosfwd>

namespace tools {

  class hexbuf_t {
  public:
    hexbuf_t(const unsigned char* buf, std::size_t size);
  public:
    const unsigned char* m_buf;
    const std::size_t m_size;
  };

  std::ostream& operator<<(std::ostream&, const hexbuf_t&);

} /* namespace tools */