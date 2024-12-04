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
    using creator_f = std::function<message_ptr(const message_t&)>;
    using creator_map_t = std::map<std::string, creator_f>;
    using module_info_t = std::tuple<const creator_map_t&, const std::string, const std::string>;
    struct module_info_pos_t {
      enum {e_creator_map, e_module_name, e_default_type};
    };
  public:
    virtual ~message_t() = default;
  public:
    static message_ptr create(const decoder_t& decoder, const std::string& stream,
        const std::string& msg, record_ptr record, const get_property_t& get_property,
        const table_manager_t& table_manager, const error_t& error);
  public:
    static const std::size_t npos;
  protected:
    message_t(const message_t& value);
    message_t(const get_property_t& get_property, const std::size_t type_idx, const fields_t& m_fields, const error_t& error);
    const std::string& type() const;
  protected:
    const get_property_t& m_get_property;
    const std::size_t m_type_idx;
    const fields_t& m_fields;
    const error_t& m_error;
    values_t m_values;
  private:
    using stream_type_idx_t = std::map<std::string, std::size_t>;
    using creator_stream_map_t = std::map<std::string, module_info_t>;
  private:
    void data(const std::size_t& idx, const std::string& field, const std::string& value) override;
    void data(const std::size_t& idx, const std::string& field, const unsigned char& value) override;
    void data(const std::size_t& idx, const std::string& field, const int& value) override;
    void data(const std::size_t& idx, const std::string& field, const long& value) override;
    void data(const std::size_t& idx, const std::string& field, const float& value) override;
    void data(const std::size_t& idx, const std::string& field, const double& value) override;
    void data(const std::size_t& idx, const std::string& field, const bool& value) override;
  private:
    static const std::size_t& msg_type_idx(const get_property_t& get_property, const std::string& stream,
       const module_info_t& info, const fields_t& fields, const error_t& error);
    static std::size_t get_type_idx(const get_property_t& getter, const module_info_t& info,
        const fields_t& fields, const error_t& error);
  private:
  private:
    static const creator_stream_map_t m_creator_stream_map;
    static std::shared_mutex m_lock_stream_type_idx;
    static stream_type_idx_t m_stream_type_idx;
  };

} /* namespace nasdaq */
