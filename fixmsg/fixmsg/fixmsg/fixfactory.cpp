#include <vector>
#include <algorithm>

#include <quickfix/Group.h>
#include <quickfix/Session.h>
#include <quickfix/FixFields.h>

#include "fixfactory.h"

namespace {

  const std::string empty_str;


  std::pair<std::string, std::string> gen_key(const FIX::Message& msg) {
    FIX::MsgType mtype;
    msg.getHeader().getField(mtype);
    const std::string key = ff::fixfactory_t::version_id(msg) + "::" + mtype.getValue();
    return {ff::fixfactory_t::version_id(msg), mtype.getValue()};
  }

/*
  std::string gen_key(const FIX::SessionID& sid, const std::string& value) {
    const std::string key = ff::fixfactory_t::version_id(sid) + std::string("::") + value;
    return key;
  }
*/

} /* namespace */

namespace ff {

  std::string fixfactory_t::version_id(const FIX::SessionID& sid) {
    return FIX::Message::toApplVerID(sid.getBeginString());
  }

  std::string fixfactory_t::version_id(const FIX::Message& msg) {
    FIX::BeginString bstr;
    msg.getHeader().getField(bstr);
    return FIX::Message::toApplVerID(bstr);
  }

  field_ptr fixfactory_t::field(const std::string& name, const std::string& value) {
    if(const auto i = field_info_by(name))
      return i->creator(value);
    return field_ptr();
  }

  field_ptr fixfactory_t::field(const int& tag, const std::string& value) {
    if(const auto i = field_info_by(tag))
      return i->creator(value);
    return field_ptr();
  }

#if 0
  group_ptr fixfactory_t::group(const FIX::SessionID& sid, const std::string& value) {
    const auto it = m_group_map.find(gen_key(sid, value));
    return it == m_group_map.end() ? group_ptr() : it->second();
  }

  fixfactory_t::group_range_t fixfactory_t::group_range(const FIX::SessionID& sid, const std::string& value) {
    using value_t = group_map_t::value_type;
    const std::string& key = gen_key(sid, value);
    auto lower = std::lower_bound(m_group_map.begin(), m_group_map.end(), key, [](const value_t& lv, const std::string& rv) {
      const std::string sl = lv.first.substr(0, std::min(lv.first.size(), rv.size()));
      return sl < rv;
    });
    auto upper = std::upper_bound(m_group_map.begin(), m_group_map.end(), key, [](const std::string& lv, const value_t& rv) {
      const std::string sr = rv.first.substr(0, std::min(rv.first.size(), lv.size()));
      return lv < sr;
    });
    return group_range_t(lower, upper);
  }

  message_ptr fixfactory_t::message(const FIX::SessionID& sid, const std::string& value) {
    const auto it = m_message_map.find(gen_key(sid, value));
    return it == m_message_map.end() ? message_ptr() : it->second();
  }

  const std::string& fixfactory_t::msg_name(const FIX::Message& msg) {
    static const std::string empty;
    auto it = m_type_map.find(gen_key(msg));
    return it == m_type_map.end() ? empty : it->second;
  }
#endif

  message_ptr fixfactory_t::message_name(const std::string& ver, const std::string& name) {
    if(const auto i = message_info_name(ver, name))
      return i->creator();
    return message_ptr();
  }

  message_ptr fixfactory_t::message_name(const FIX::SessionID& sid, const std::string& name) {
    return message_name(version_id(sid), name);
  }

  message_ptr fixfactory_t::message_name(const FIX::Message& msg, const std::string& name) {
    return message_name(version_id(msg), name);
  }

  message_ptr fixfactory_t::message_type(const std::string& ver, const std::string& type) {
    if(const auto i = message_info_type(ver, type))
      return i->creator();
    return message_ptr();
  }

  message_ptr fixfactory_t::message_type(const FIX::SessionID& sid, const std::string& type) {
    return message_type(version_id(sid), type);
  }

  message_ptr fixfactory_t::message_type(const FIX::Message& msg, const std::string& type) {
    return message_type(version_id(msg), type);
  }

  const std::string& fixfactory_t::msg_name(const FIX::Message& msg) {
    const auto key = gen_key(msg);
    if(const auto i = message_info_name(key.first, key.second))
      return i->name;
    return empty_str;
  }

} /* namespace ff */
