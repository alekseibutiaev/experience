#include <limits>
#include <string>
#include <mutex>
#include <iterator>
#include <atomic>
#include <stdexcept>

#include "tw/tw_types.h"

#include "location.h"
#include "error.h"
#include "table_manager.h"
#include "decoder.h"

#include "message.h"

namespace {


}; /* namespace */

namespace nasdaq {

  const std::size_t message_t::npos = std::numeric_limits<std::size_t>::max();

  const message_t::creators_stream_map_t message_t::m_creator_stream_map = {
    message_t::creators_stream_map_t::value_type("TOTALVIEW", tw::get_modile_info_t()()),
    message_t::creators_stream_map_t::value_type("QBBO-B-CORE-V2", tw::get_modile_info_t()())
  };

  message_t::topics_msg_t message_t::m_topics_msg;

  std::shared_mutex message_t::m_lock_stream_type_idx;

  message_t::stream_type_idx_t message_t::m_stream_type_idx;

  message_t::message_t(const message_t& value)
      : m_sn(value.m_sn)
      , m_type_idx(value.m_type_idx)
      , m_error(value.m_error)
      , m_get_property(value.m_get_property)
      , m_fields(value.m_fields)
      , m_values(value.m_values) {
  }

  message_t::message_t(const std::size_t sn, const std::size_t type_idx, const error_t& error,
        const get_property_t& get_property, const fields_t& fields)
      : m_sn(sn)
      , m_type_idx(type_idx)
      , m_error(error)
      , m_get_property(get_property)
      , m_fields(fields)
      , m_values(m_fields.size()) {
  }

  const long& message_t::sequence() const {
    static const long res = std::numeric_limits<std::ptrdiff_t>::min();
    return res;
  }

  const std::string& message_t::topic() const {
    static const std::string res = "UNKNOWN";
    return res;
  }

  message_t::messages_sequence_t& message_t::sequence_list() const {
    static messages_sequence_t tmp;
    return tmp;
  }

  const std::size_t& message_t::sn() const {
    return m_sn;
  }

  const std::string& message_t::type() const {
    return std::get<std::string>(m_values[m_type_idx]);
  }

  void message_t::visitor(message_visitor_t&) const {
  }

  message_uptr message_t::create(const std::string& stream, const std::string& msg, const std::size_t& sn,
        record_ptr record, const decoder_t& decoder, const get_property_t& get_property,
        const table_manager_t& table_manager, const error_t& error, const time_point_t& tp,
        const creators_stream_map_t& creators) {
    struct init_flag{ std::atomic_flag value = ATOMIC_FLAG_INIT; };
    static std::vector<init_flag> ut('Z' - 'A' + 1);
    for(auto it = creators.find(stream); it != creators.end();) {
      const auto& fields = table_manager.get_fields(stream, msg);
      if(!fields.empty()) {
        const auto& type_idx = msg_type_idx(get_property, stream, it->second, fields, error);
        message_t tmp(sn, type_idx, error, get_property, fields);
        decoder.get_field(record, type_idx, tmp);
        const auto& type = tmp.type();
        if(auto msg = std::get<module_info_pos_t::e_creator_map>(it->second)[type[0] - 'A'](tmp)) {
          for(std::size_t idx = 0; idx < fields.size(); ++idx)
            if(idx != type_idx)
              decoder.get_field(record, idx, *msg);
          return msg;
        }
        if(!ut[type[0] - 'A'].value.test_and_set())
          error.error("unsupported message type: [" + type + "]" + __FILE_STR__);
        return message_uptr();
      }
      error.error("unsupported stream: [" + stream + "] message: [" + msg + "]" +__FILE_STR__);
      return message_uptr();
    }
    error.error("unsupported stream: [" + stream + "]" + __FILE_STR__);
    return message_uptr();
  }

  void message_t::reset() {
    for(auto& it : m_topics_msg)
      *it = messages_sequence_t();
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const std::string& value) {
    (void)field;
    m_values[idx] = value;
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const unsigned char& value) {
    (void)field;
    m_values[idx] = value;
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const int& value) {
    (void)field;
    m_values[idx] = value;
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const long_wrp_t& value) {
    (void)field;
    m_values[idx] = static_cast<long>(value);
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const float& value) {
    (void)field;
    m_values[idx] = value;
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const double& value) {
    (void)field;
    m_values[idx] = value;
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const bool& value) {
    (void)field;
    m_values[idx] = value;
  };

  void message_t::data(const std::size_t& idx, const std::string& field, const time_point_t& value) {
    (void)field;
    m_values[idx] = value;
  }

  const std::size_t& message_t::msg_type_idx(const get_property_t& get_property,
      const std::string& stream, const module_info_t& info, const fields_t& fields,
      const error_t& error) {
    {
      std::shared_lock _(m_lock_stream_type_idx);
      for(auto it = m_stream_type_idx.find(stream); it != m_stream_type_idx.end();)
        return it->second;
    }
    for(const auto idx = get_type_idx(get_property, info, fields, error); message_t::npos != idx;) {
      std::unique_lock _(m_lock_stream_type_idx);
      return m_stream_type_idx[stream] = idx;
    }
    return message_t::npos;
  }

  std::size_t message_t::get_type_idx(const get_property_t& get_property, const module_info_t& info,
        const fields_t& fields, const error_t& error) {
    const auto& name = get_property(std::get<module_info_pos_t::e_module_name>(info) +
      "/name_msg_type").value_or(std::get<module_info_pos_t::e_default_type>(info));
    for(const auto it = std::find(fields.begin(), fields.end(), name); it != fields.end();)
      return static_cast<std::size_t>(std::distance(fields.begin(), it));
    error.error("fields name: " + name + " unsupported." + __FILE_STR__);
    return message_t::npos;
  }

} /* namespace nasdaq */
