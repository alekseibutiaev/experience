#pragma once

#include <iosfwd>
#include <iomanip>
#include <variant>
#include <optional>

#include "../types.h"
#include "../message.h"

namespace nasdaq {

  namespace dom {

    class get_modile_info_t {
    public:
      const message_t::module_info_t operator()() const;
    private:
      static const message_t::creator_map_t m_creators;
    };

    class get_type_idx {
    public:
      std::size_t& operator()(const get_property_t& getter, const fields_t& fields) const;
    private:
      static std::size_t m_idx;
    };

  } /* namespace dom */

} /* namespace nasdaq */
