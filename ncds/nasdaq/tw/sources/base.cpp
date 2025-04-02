#include "../tw_visitor.h"
#include "base.h"


namespace nasdaq {

  namespace tw {

    base_t::base_t(const message_t& value) : message_t(value) {
    }

    const long& base_t::sequence() const {
      return std::get<long>(m_values[e_sequence]);
    }

  } /* namespace tw */

} /* namespace nasdaq */