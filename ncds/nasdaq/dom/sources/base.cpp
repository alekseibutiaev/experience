#include "../dom_visitor.h"
#include "base.h"


namespace nasdaq {

  namespace dom {

    base_t::base_t(const message_t& value) : message_t(value) {
    }

    const long& base_t::sequence() const {
      return std::get<long>(m_values[e_sequence]);
    }

  } /* namespace dom */

} /* namespace nasdaq */