#pragma once

#include <map>
#include <memory>
#include <string>

#include <quickfix/Field.h>
#include <quickfix/Group.h>
#include <quickfix/Message.h>
#include <quickfix/SessionID.h>

namespace ff {

  using field_ptr = std::unique_ptr<FIX::FieldBase>;
  using group_ptr = std::unique_ptr<FIX::Group>;
  using message_ptr = std::unique_ptr<FIX::Message>;

  class fixfactory_t {
  public:
    using field_func_t = field_ptr(*)(const std::string&);
    using field_map_t = std::map<std::string, field_func_t>;
    using group_func_t = group_ptr(*)();
    using group_map_t = std::map<std::string, group_func_t>;
    using msg_func_t = message_ptr(*)();
    using message_map_t = std::map<std::string, msg_func_t>;
    using group_range_t = std::pair<group_map_t::const_iterator, group_map_t::const_iterator>;
    using type_map_t = std::map<std::string, std::string>;

    struct field_info_t {
      const std::string name;
      const int tag;
      const field_func_t create;
      const bool is_group;
    };

    struct group_info_t {
      using group_map_tt = std::map<std::string, group_info_t>;
      const group_func_t create;
      const group_map_tt sub_group;
    } mm;
    
    struct message_info_t {
      const std::string ver_id;
      const std::string type;
      const std::string name;
      const msg_func_t creator;
      const group_info_t::group_map_tt sub_group;
    };

  public:
    static std::string version_id(const FIX::SessionID& sid);
    static std::string version_id(const FIX::Message& msg);
    static const field_info_t* field_info_by(const std::string& name);
    static const field_info_t* field_info_by(const int& tag);
    static field_ptr field(const std::string& name, const std::string& value = std::string());
    static field_ptr field(const int& tar, const std::string& value = std::string());
    static group_ptr group(const FIX::SessionID& sid, const std::string& value);
    static group_range_t group_range(const FIX::SessionID& sid, const std::string& value);
    static message_ptr message(const FIX::SessionID& sid, const std::string& value);
    static const std::string& msg_name(const FIX::Message& msg);

  private:
    //static const field_map_t m_field_map;
    static const group_map_t m_group_map;
    static const message_map_t m_message_map;
    static const type_map_t m_type_map;
  }; 

} /* namespace ff */
