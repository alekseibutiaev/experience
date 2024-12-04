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
      return message_t::module_info_t(m_creators, "dom");
    }

    std::size_t get_type_idx::m_idx = std::numeric_limits<std::size_t>::max();

    std::size_t& get_type_idx::operator()(const get_property_t& getter, const fields_t& fields) const {
      if(std::numeric_limits<std::size_t>::max() == m_idx) {
        const auto tmp = getter("dom/name_msg_type").value_or("msgType");
        m_idx = std::distance(fields.begin(), std::find(fields.begin(), fields.end(), tmp));
      }
      return m_idx;
    }

  } /* namespace dom */

} /* namespace nasdaq */
