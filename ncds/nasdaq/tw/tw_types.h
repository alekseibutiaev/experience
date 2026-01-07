#pragma once

#include <iosfwd>
#include <iomanip>
#include <variant>
#include <optional>

#include "../types.h"
#include "../message.h"

namespace nasdaq {

  namespace tw {

    class get_modile_info_t {
    public:
      const message_t::module_info_t operator()() const;
    private:
      static const message_t::creators_t m_creators;
    };

  } /* namespace tw */

} /* namespace nasdaq */
