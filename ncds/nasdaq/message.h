#pragma once

#include <map>
#include <list>
#include <array>
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
  class message_visitor_t;

  using message_uptr = std::unique_ptr<class message_t>;
  using message_ptr = std::shared_ptr<class message_t>;

  class message_t : public data_delegate_t {
  public:
    using creator_f = std::function<message_uptr(const message_t&)>;
    using creators_t = std::array<creator_f, static_cast<std::size_t>('Z' - 'A' + 1)>;
    using module_info_t = std::tuple<const creators_t&, const std::string, const std::string>;
    using creators_stream_map_t = std::map<std::string, module_info_t>;
    using messages_t = std::list<message_ptr>;
    using messages_sequence_t = std::pair<messages_t, std::size_t>;
    using messages_sequence_ptr = std::shared_ptr<messages_sequence_t>;
    struct module_info_pos_t {
      enum { e_creator_map, e_module_name, e_default_type };
    };
  public:
    virtual ~message_t() = default;
    const std::size_t& sn() const;
    virtual const long& sequence() const;
    virtual const std::string& topic() const;
    virtual messages_sequence_t& sequence_list() const;
    const std::string& type() const;
    virtual void visitor(message_visitor_t& visitor) const;
  public:
    static message_uptr create(const std::string& stream, const std::string& msg,
        const std::size_t& sn, const record_ptr record, const decoder_t& decoder,
        const get_property_t& get_property, const table_manager_t& table_manager,
        const error_t& error, const time_point_t& tp,
        const creators_stream_map_t& creators = message_t::m_creator_stream_map);
    static void reset();
  public:
    static const std::size_t npos;
  protected:
    using topics_msg_t = std::list<messages_sequence_ptr>;
  protected:
    message_t(const message_t& value);
    message_t(const std::size_t first, const std::size_t type_idx, const error_t& error,
      const get_property_t& get_property, const fields_t& fields);
  protected:
    static topics_msg_t m_topics_msg;
  protected:
    const std::size_t m_sn;
    const std::size_t m_type_idx;
    const error_t& m_error;
    const get_property_t& m_get_property;
    const fields_t& m_fields;
    values_t m_values;
  private:
    using stream_type_idx_t = std::map<std::string, std::size_t>;
  private:
    void data(const std::size_t& idx, const std::string& field, const std::string& value) override;
    void data(const std::size_t& idx, const std::string& field, const unsigned char& value) override;
    void data(const std::size_t& idx, const std::string& field, const int& value) override;
    void data(const std::size_t& idx, const std::string& field, const long_wrp_t& value) override;
    void data(const std::size_t& idx, const std::string& field, const float& value) override;
    void data(const std::size_t& idx, const std::string& field, const double& value) override;
    void data(const std::size_t& idx, const std::string& field, const bool& value) override;
    void data(const std::size_t& idx, const std::string& field, const time_point_t& value) override;
  private:
    static const std::size_t& msg_type_idx(const get_property_t& get_property, const std::string& stream,
       const module_info_t& info, const fields_t& fields, const error_t& error);
    static std::size_t get_type_idx(const get_property_t& getter, const module_info_t& info,
        const fields_t& fields, const error_t& error);
  private:
    static const creators_stream_map_t m_creator_stream_map;
    static std::shared_mutex m_lock_stream_type_idx;
    static stream_type_idx_t m_stream_type_idx;
  };

} /* namespace nasdaq */
