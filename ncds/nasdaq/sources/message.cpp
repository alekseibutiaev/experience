#include <limits>
#include <string>
#include <stdexcept>

#include "dom/dom_types.h"
#include "accessor/table_manager.h"

#include "location.h"
#include "error.h"
#include "message.h"

namespace {


}; /* namespace */

namespace nasdaq {

  std::shared_mutex message_t::m_lock_stream_idx;
  message_t::stream_idx_t message_t::m_stream_idx;

  const message_t::creator_stream_map_t message_t::m_creator_stream_map = {
    message_t::creator_stream_map_t::value_type("TOTALVIEW", dom::get_modile_info_t()())
  };

  message_t::message_t(const get_property_t& get_property, const error_t& error)
      : m_get_property(get_property)
      , m_error(error) {
  }

  message_ptr message_t::create(const acc::avro_decode_t& decode, const std::string& stream,
        const std::string& msg, acc::avro_record_t record, const get_property_t& get_property,
        const acc::table_manager_t& table_manager, const error_t& error) {


    return message_ptr();
  }

#if 0

  const std::size_t& message_t::msg_type_idx(const get_property_t& get_property, const std::string& stream,
      const fields_t& fields) {

    {
      std::shared_lock _(m_lock_stream_idx);
      auto it = m_stream_idx.find(stream);
      if(it != m_stream_idx.end())
        return it->second;
    }
    std::unique_lock _(m_lock_stream_idx);
    return m_stream_idx[stream] = dom::get_type_idx()(get_property(), fields);
    return 0;
  }
#endif 


} /* namespace nasdaq */
