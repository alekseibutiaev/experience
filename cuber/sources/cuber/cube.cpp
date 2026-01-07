#include "cube.h"

namespace cr {

  pos_t::pos_t(const short x, const short y, const short z)
      : m_x(x)
      , m_y(y)
      , m_z(z) {
  }

  pos_t::pos_t(const std::size_t idx)
     : m_x(pos[idx].m_x)
     , m_y(pos[idx].m_y)
     , m_z(pos[idx].m_z) {
  }

  pos_t pos_t::pos[27] = {
    pos_t(-1,  1,  1), pos_t( 0,  1,  1), pos_t( 1,  1,  1),
    pos_t(-1,  1,  0), pos_t( 0,  1,  0), pos_t( 1,  1,  0),
    pos_t(-1,  1, -1), pos_t( 0,  1, -1), pos_t( 1,  1, -1),

    pos_t(-1,  0,  1), pos_t( 0,  0,  1), pos_t( 1,  0,  1),
    pos_t(-1,  0,  0), pos_t( 0,  0,  0), pos_t( 1,  0,  0),
    pos_t(-1,  0, -1), pos_t( 0,  0, -1), pos_t( 1,  0, -1),

    pos_t(-1, -1,  1), pos_t( 0, -1,  1), pos_t( 1, -1,  1),
    pos_t(-1, -1,  0), pos_t( 0, -1,  0), pos_t( 1, -1,  0),
    pos_t(-1, -1, -1), pos_t( 0, -1, -1), pos_t( 1, -1, -1),
  };

  cube_t::cube_t(std::size_t tpos, std::size_t cpos)
    : m_tpos(pos_t::pos[tpos])
    , m_cpos(pos_t::pos[cpos]) {
  }


}; /* namespace cr */
