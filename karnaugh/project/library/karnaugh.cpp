#include <iostream>
#include "karnaugh.h"
#include "gray.h"

namespace {

  std::size_t make_mask(std::size_t val) {
    std::size_t res = 0;
    while(val--) {
      res <<= 1;
      res |= 1;
    }
    return res;
  }

} /* namespace */

namespace kh {

  void print(int a) {
    std::cout << a << std::endl;
  }

  khmap_t::khmap_t(const std::size_t& values)
    : m_array(1 << (values / 2 + values % 2), row_t(1 << (values / 2), 0))
    , m_y_shift(values / 2 + values % 2)
    , m_x_mask(make_mask(values / 2))
    , m_y_mask(make_mask(values / 2 + values % 2)){
  }

  void khmap_t::set(const std::size_t& cell, const unsigned char& value) {
    const auto x = from_gray(cell & m_x_mask);
    const auto y = from_gray(cell >> m_y_shift & m_y_mask);
    m_array[y][x] = value;
  }

  void khmap_t::print() const {
    std::cout << m_array.size() << " " << m_array[0].size() << std::endl;
    for(std::size_t y = 0; y < m_array.size(); ++y) {
      for(std::size_t x = 0; x < m_array[0].size(); ++x) {
        std::cout << " " << std::size_t(m_array[y][x]);
      }
      std::cout << std::endl;
    }
  }

} /* namespace kh */
