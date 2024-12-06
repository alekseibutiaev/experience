#include <limits>
#include <string>
#include <iterator>
#include <stdexcept>

#include "dom/dom_types.h"

#include "location.h"
#include "error.h"
#include "table_manager.h"
#include "decoder.h"

#include "message.h"

namespace {


}; /* namespace */

namespace nasdaq {

  const std::size_t message_t::npos = std::numeric_limits<std::size_t>::max();

  const message_t::creator_stream_map_t message_t::m_creator_stream_map = {
    message_t::creator_stream_map_t::value_type("TOTALVIEW", dom::get_modile_info_t()())
  };

  std::shared_mutex message_t::m_lock_stream_type_idx;

  message_t::stream_type_idx_t message_t::m_stream_type_idx;

  message_t::message_t(const message_t& value)
      : m_get_property(value.m_get_property)
      , m_type_idx(value.m_type_idx)
      , m_fields(value.m_fields)
      , m_error(value.m_error)
      , m_values(value.m_values) {
  }

  message_t::message_t(const get_property_t& get_property, const std::size_t type_idx,
        const fields_t& fields, const error_t& error)
      : m_get_property(get_property)
      , m_type_idx(type_idx)
      , m_fields(fields)
      , m_error(error)
      , m_values(m_fields.size()) {
  }

  const std::string& message_t::type() const {
    return std::get<std::string>(m_values[m_type_idx]);
  }

  message_ptr message_t::create(const decoder_t& decoder, const std::string& stream,
        const std::string& msg, record_ptr record, const get_property_t& get_property,
        const table_manager_t& table_manager, const error_t& error) {
    for(auto it = m_creator_stream_map.find(stream); it != m_creator_stream_map.end();) {
      const auto fields = table_manager.get_fields(stream, msg);
      const auto& type_idx = msg_type_idx(get_property, stream, it->second, fields, error);
      message_t tmp(get_property, type_idx, fields, error);
      decoder.get_field(record, type_idx, tmp);
      const std::string v = tmp.type();
      error.info(v);
    }
    

    error.error("unsupported stream: " + stream + __FILE_STR__);
    return message_ptr();
  }

  void message_t::data(const std::size_t& idx, const std::string& field, const std::string& value) {
    m_values[idx] = value;
  }
  void message_t::data(const std::size_t& idx, const std::string& field, const unsigned char& value) {
    m_values[idx] = value;
  }
  void message_t::data(const std::size_t& idx, const std::string& field, const int& value) {
    m_values[idx] = value;
  }
  void message_t::data(const std::size_t& idx, const std::string& field, const long_wrp_t& value) {
    m_values[idx] = static_cast<long>(value);
  }
  void message_t::data(const std::size_t& idx, const std::string& field, const float& value) {
    m_values[idx] = value;
  }
  void message_t::data(const std::size_t& idx, const std::string& field, const double& value) {
    m_values[idx] = value;
  }
  void message_t::data(const std::size_t& idx, const std::string& field, const bool& value) {
    m_values[idx] = value;
  };
  void message_t::data(const std::size_t& idx, const std::string& field, const time_point_t& value) {
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
    const auto idx = get_type_idx(get_property, info, fields, error);
    if(message_t::npos != idx) {
      std::unique_lock _(m_lock_stream_type_idx);
      return m_stream_type_idx[stream] = idx;
    }
    return message_t::npos;
  }

  std::size_t message_t::get_type_idx(const get_property_t& get_property, const module_info_t& info,
        const fields_t& fields, const error_t& error) {
    const auto& name = get_property(std::get<module_info_pos_t::e_module_name>(info) +
      "/name_msg_type").value_or(std::get<module_info_pos_t::e_default_type>(info));
    const auto it = std::find(fields.begin(), fields.end(), name);
    if(it != fields.end())
      return static_cast<std::size_t>(std::distance(fields.begin(), it));
    error.error("fields name: " + name + " unsupported." + __FILE_STR__);
    return message_t::npos;
  }

} /* namespace nasdaq */
