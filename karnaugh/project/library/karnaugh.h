#pragma once

#include <vector>

namespace kh {

  void print(int a);

  class khmap_t {
  public:
    using value_t = unsigned char;
  public:
    khmap_t(const std::size_t& values);
    void set(const std::size_t& cell, const value_t& value);
    void print() const;
  private:
    using row_t = std::vector<value_t>;
    using array_t = std::vector<row_t>;
  private:
  private:
    array_t m_array;
    const std::size_t m_y_shift;
    const std::size_t m_x_mask;
    const std::size_t m_y_mask;
  }; /* class khmap_t */

} /* namespace kh */
