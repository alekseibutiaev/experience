#include <iostream>
#include <karnaugh.h>

namespace {

  std::size_t grayencode(std::size_t g) {
      return g ^ (g >> 1);
  }

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
    : m_array(values / 2, col_t(values / 2 + values % 2, 0))
    , m_y_shift(values / 2 + values % 2)
    , m_x_mask(make_mask(values / 2 + values % 2))
    , m_y_mask(make_mask(values / 2)){
  }

  void khmap_t::set(const std::size_t& cell, const unsigned char& value) {
    const auto a = cell & m_x_mask;
    const auto b = cell >> m_y_shift;
    const std::size_t xi = grayencode(a);
    const std::size_t yi = grayencode(b);
    std::cout << xi << " " << yi << " " << a << " " << b  << std::endl;
    std::cout << xi + (yi << m_y_shift) << std::endl;

  }

  void khmap_t::print() const {

  }

} /* namespace kh */
