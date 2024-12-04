#include <limits>
#include <memory>
#include <iterator>
#include <algorithm>

#include "../dom_types.h"
#include "../../message.h"
#include "../messages.h"

namespace nasdaq {

  namespace dom {

    const message_t::creator_map_t get_modile_info_t::m_creators = {
      message_t::creator_map_t::value_type("A", [](const message_t& value){return std::make_unique<add_order_t>(value);}),
      message_t::creator_map_t::value_type("X", [](const message_t& value){return std::make_unique<order_cancel_t>(value);}),
      message_t::creator_map_t::value_type("D", [](const message_t& value){return std::make_unique<order_delete_t>(value);}),
      message_t::creator_map_t::value_type("E", [](const message_t& value){return std::make_unique<order_executed_t>(value);}),
      message_t::creator_map_t::value_type("C", [](const message_t& value){return std::make_unique<order_executed_with_price_t>(value);}),
      message_t::creator_map_t::value_type("S", [](const message_t& value){return std::make_unique<system_event_t>(value);})
    };

    const message_t::module_info_t get_modile_info_t::operator()() const {
      return message_t::module_info_t(m_creators, "dom", "msgType");
    }

  } /* namespace dom */

} /* namespace nasdaq */
