#pragma once

#include <cstddef>

namespace cr {

  struct pos_t {
    pos_t(const short x, const short y, const short z);
    pos_t(const std::size_t idx);
    short m_x, m_y, m_z;
    static pos_t pos[27];
  };

  class cube_t {
    cube_t(std::size_t tpos, std::size_t cpos);
  private:
    const pos_t& m_tpos;
    pos_t m_cpos;
  };

}; /* namespace cr */
