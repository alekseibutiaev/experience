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
  public:
    static field_ptr field(const std::string& name, const std::string& value);
    static group_ptr group(const FIX::SessionID& sid, const std::string& value);
    static group_range_t group_range(const FIX::SessionID& sid, const std::string& value);
    static message_ptr message(const FIX::SessionID& sid, const std::string& value);
  private:
    static const field_map_t m_field_map;
    static const group_map_t m_group_map;
    static const message_map_t m_message_map;
    static const type_map_t m_type_map;
  }; 

} /* namespace ff */
