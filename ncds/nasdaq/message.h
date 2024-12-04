#pragma once

#include <map>
#include <string>
#include <memory>
#include <shared_mutex>

#include "types.h"

#include "data_delegate.h"

namespace nasdaq {

  class error_t;

  namespace acc {

    class avro_decode_t;
    class table_manager_t;
    class avro_record_t;

  }

  using message_ptr = std::unique_ptr<class message_t>;

  class message_t : public data_delegate_t {
  public:
    using creator_f = std::function<message_ptr()>;
    using creator_map_t = std::map<std::string, creator_f>;
    using module_info_t = std::pair<const creator_map_t&, std::string>;
  public:
    message_t(const get_property_t& get_property, const error_t& error);
    virtual ~message_t() = default;
  public:
    static message_ptr create(const acc::avro_decode_t& decode, const std::string& stream,
        const std::string& msg, acc::avro_record_t record, const get_property_t& get_property,
        const acc::table_manager_t& table_manager, const error_t& error);
  private:
    using stream_idx_t = std::map<std::string, std::size_t>;
    using creator_stream_map_t = std::map<std::string, module_info_t>;
  private:
    //static const std::size_t& msg_type_idx(const get_property_t& get_property, const std::string& stream);
  private:
    const get_property_t& m_get_property;
    const error_t& m_error;
    //const std::size_t m_type_idx;
    //const acc::table_manager_t& m_table_manager;
  private:
    static std::shared_mutex m_lock_stream_idx;
    static stream_idx_t m_stream_idx;
    static const creator_stream_map_t m_creator_stream_map;
    //static const stream_index_map_t m_stream_index_map;
  };

} /* namespace nasdaq */
