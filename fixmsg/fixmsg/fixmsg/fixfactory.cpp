#include <vector>
#include <iterator>
#include <algorithm>

#include <quickfix/Group.h>
#include <quickfix/Session.h>
#include <quickfix/Exceptions.h>
#include <quickfix/FixFields.h>

#include "fixfactory.h"

#if 0

#include "Common.h"
#undef LOG_NAME
#define LOG_NAME "MFIX"

#define ENDL 

#else

#define LOG_DEBUG std::cout
#define ENDL std::endl
#endif


namespace {

  using csit_t = ff::strings_t::const_iterator;

  const std::string empty_str;

  std::pair<std::string, std::string> gen_key(const FIX::Message& msg) {
    FIX::MsgType mtype;
    msg.getHeader().getField(mtype);
    return {ff::fixfactory_t::version_id(msg), mtype.getValue()};
  }

  ff::group_uptr get_group_creator(const ff::fixfactory_t::group_info_t::group_map_t& map, csit_t begin, csit_t end) {
    auto it = map.find(*begin);
    if(it != map.end()) {
      if(1 == std::distance(begin, end))
        return it->second.creator();
      return get_group_creator(it->second.sub_group, ++begin, end);
    }
    return ff::group_uptr();
  }

} /* namespace */

namespace ff {

  std::string fixfactory_t::version_id(const FIX::SessionID& sid) {
    if(sid.isFIXT()) {
      if(FIX::Session* pSession = FIX::Session::lookupSession(sid)) {
        FIX::ApplVerID applVerID = pSession->getSenderDefaultApplVerID();
        std::string r = applVerID.getString();
        return r;
      }
      return std::string();
    }
    else
      return FIX::Message::toApplVerID(sid.getBeginString());
  }

  std::string fixfactory_t::version_id(const FIX::Message& msg) {
    FIX::BeginString bstr;
    msg.getHeader().getField(bstr);
    if(bstr.getString() == FIX::BeginString_FIXT11) {
      try {
        FIX::ApplVerID ver;
        msg.getHeader().getField(ver);
        return ver.getString();
      }
      catch(const FIX::FieldNotFound& e) {
        LOG_DEBUG << e.what() << "field: " << e.field << ENDL;
      }
      return "7";
    }
    return FIX::Message::toApplVerID(bstr);
  }

  field_uptr fixfactory_t::field(const std::string& name, const std::string& value) {
    if(const auto i = field_info_by(name))
      return i->creator(value);
    return field_uptr();
  }

  field_uptr fixfactory_t::field(const int& tag, const std::string& value) {
    if(const auto i = field_info_by(tag))
      return i->creator(value);
    return field_uptr();
  }

  const fixfactory_t::message_info_t* fixfactory_t::message_info_name(const FIX::SessionID& sid, const std::string& name) {
    return message_info_name(version_id(sid), name);
  }

  const fixfactory_t::message_info_t* fixfactory_t::message_info_name(const FIX::Message& msg, const std::string& name) {
    return message_info_name(version_id(msg), name);
  }

  const fixfactory_t::message_info_t* fixfactory_t::message_info_type(const FIX::SessionID& sid, const std::string& type) {
    return message_info_type(version_id(sid), type);
  }

  const fixfactory_t::message_info_t* fixfactory_t::message_info_type(const FIX::Message& msg, const std::string& type) {
    return message_info_type(version_id(msg), type);
  }

  group_uptr fixfactory_t::group(const message_info_t* info, const strings_t& path){
    return get_group_creator(info->sub_group, path.begin(), path.end());
  }

  message_uptr fixfactory_t::message_name(const std::string& ver, const std::string& name) {
    if(const auto i = message_info_name(ver, name))
      return i->creator();
    return message_uptr();
  }

  message_uptr fixfactory_t::message_name(const FIX::SessionID& sid, const std::string& name) {
    return message_name(version_id(sid), name);
  }

  message_uptr fixfactory_t::message_name(const FIX::Message& msg, const std::string& name) {
    return message_name(version_id(msg), name);
  }

  message_uptr fixfactory_t::message_type(const std::string& ver, const std::string& type) {
    if(const auto i = message_info_type(ver, type))
      return i->creator();
    return message_uptr();
  }

  message_uptr fixfactory_t::message_type(const FIX::SessionID& sid, const std::string& type) {
    return message_type(version_id(sid), type);
  }

  message_uptr fixfactory_t::message_type(const FIX::Message& msg, const std::string& type) {
    return message_type(version_id(msg), type);
  }

  const std::string& fixfactory_t::msg_name(const FIX::Message& msg) {
    const auto key = gen_key(msg);
    if(const auto i = message_info_type(key.first, key.second))
      return i->name;
    return empty_str;
  }

} /* namespace ff */
