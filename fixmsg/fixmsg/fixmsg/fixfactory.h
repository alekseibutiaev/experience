#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <quickfix/Field.h>
#include <quickfix/Group.h>
#include <quickfix/Message.h>
#include <quickfix/SessionID.h>

namespace ff {

  using strings_t = std::vector<std::string>;

  using field_ptr = std::unique_ptr<FIX::FieldBase>;
  using group_ptr = std::unique_ptr<FIX::Group>;
  using message_ptr = std::unique_ptr<FIX::Message>;

  class fixfactory_t {
  public:

    using field_creator_f = field_ptr(*)(const std::string&);
    using group_creator_f = group_ptr(*)();
    using msg_creator_f = message_ptr(*)();

    struct field_info_t {
      const std::string name;
      const int tag;
      const field_creator_f creator;
      const bool is_group;
    };

    struct group_info_t {
      using group_map_t = std::map<std::string, group_info_t>;
      const group_creator_f creator;
      const group_map_t sub_group;
    };
    
    struct message_info_t {
      const std::string ver;
      const std::string type;
      const std::string name;
      const msg_creator_f creator;
      const group_info_t::group_map_t sub_group;
    };

  public:

    static std::string version_id(const FIX::SessionID& sid);
    static std::string version_id(const FIX::Message& msg);
    static const field_info_t* field_info_by(const std::string& name);
    static const field_info_t* field_info_by(const int& tag);
    static field_ptr field(const std::string& name, const std::string& value = std::string());
    static field_ptr field(const int& tar, const std::string& value = std::string());
    static const message_info_t* message_info_name(const std::string& ver, const std::string& name);
    static const message_info_t* message_info_name(const FIX::SessionID& sid, const std::string& name);
    static const message_info_t* message_info_name(const FIX::Message& msg, const std::string& name);
    static const message_info_t* message_info_type(const std::string& ver, const std::string& type);
    static const message_info_t* message_info_type(const FIX::SessionID& sid, const std::string& type);
    static const message_info_t* message_info_type(const FIX::Message& msg, const std::string& type);

    static group_ptr group(const message_info_t* info, const strings_t& path);

    static message_ptr message_name(const std::string& ver, const std::string& name);
    static message_ptr message_name(const FIX::SessionID& sid, const std::string& name);
    static message_ptr message_name(const FIX::Message& msg, const std::string& name);

    static message_ptr message_type(const std::string& ver, const std::string& type);
    static message_ptr message_type(const FIX::SessionID& sid, const std::string& type);
    static message_ptr message_type(const FIX::Message& msg, const std::string& type);

    static const std::string& msg_name(const FIX::Message& msg);
  }; 

} /* namespace ff */
