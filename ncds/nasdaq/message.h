#pragma once

#include <map>
#include <tuple>
#include <string>
#include <memory>
#include <shared_mutex>

#include "types.h"

#include "data_delegate.h"

namespace nasdaq {

  class error_t;
  class decoder_t;
  class table_manager_t;


  using message_ptr = std::unique_ptr<class message_t>;

  class message_t : public data_delegate_t {
  public:
    using creator_f = std::function<message_ptr()>;
    using creator_map_t = std::map<std::string, creator_f>;
    using module_info_t = std::tuple<const creator_map_t&, const std::string, const std::string>;
    struct info_pos_t {
      enum {e_creator_map, e_module_name, e_default_type};
    };
  public:
    message_t(const get_property_t& get_property, const error_t& error);
    virtual ~message_t() = default;
  public:
    static message_ptr create(const decoder_t& decode, const std::string& stream,
        const std::string& msg, record_ptr record, const get_property_t& get_property,
        const table_manager_t& table_manager, const error_t& error);
  public:
    static const std::size_t npos;
  private:
    using stream_type_idx_t = std::map<std::string, std::size_t>;
    using creator_stream_map_t = std::map<std::string, module_info_t>;
  private:
    static const std::size_t& msg_type_idx(const get_property_t& get_property, const std::string& stream,
       const module_info_t& info, const fields_t& fields, const error_t& error);
    static std::size_t get_type_idx(const get_property_t& getter, const module_info_t& info,
        const fields_t& fields, const error_t& error);
  private:
    const get_property_t& m_get_property;
    const error_t& m_error;
    //const std::size_t m_type_idx;
    //const acc::table_manager_t& m_table_manager;
  private:
    static std::shared_mutex m_lock_stream_type_idx;
    static stream_type_idx_t m_stream_type_idx;
    static const creator_stream_map_t m_creator_stream_map;
    //static const stream_index_map_t m_stream_index_map;
  };

} /* namespace nasdaq */
