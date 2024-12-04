#include <limits>
#include <memory>
#include <iterator>
#include <algorithm>

#include "../dom_types.h"
#include "../message.h"

namespace nasdaq {

  namespace dom {

    const message_t::creator_map_t get_modile_info_t::m_creators = {
      message_t::creator_map_t::value_type("A", []{return std::unique_ptr<add_order_t>();}),
      message_t::creator_map_t::value_type("X", []{return std::unique_ptr<order_cancel_t>();}),
      message_t::creator_map_t::value_type("D", []{return std::unique_ptr<order_delete_t>();}),
      message_t::creator_map_t::value_type("E", []{return std::unique_ptr<order_executed_t>();}),
      message_t::creator_map_t::value_type("C", []{return std::unique_ptr<order_executed_with_price_t>();}),
      message_t::creator_map_t::value_type("S", []{return std::unique_ptr<system_event_t>();})
    };

    const message_t::module_info_t get_modile_info_t::operator()() const {
      return message_t::module_info_t(m_creators, "dom", "msgType");
    }

  } /* namespace dom */

} /* namespace nasdaq */
