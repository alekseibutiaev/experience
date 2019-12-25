#include <vector>
#include <algorithm>

#include <quickfix/Group.h>
#include <quickfix/Session.h>
#include <quickfix/FixFields.h>

#include "fixfactory.h"

namespace {

  std::string gen_key(const FIX::Message& msg) {
    FIX::MsgType mtype;
    msg.getHeader().getField(mtype);
    const std::string key = ff::fixfactory_t::version_id(msg) + "::" + mtype.getValue();
    return key;
  }

  std::string gen_key(const FIX::SessionID& sid, const std::string& value) {
    const std::string key = ff::fixfactory_t::version_id(sid) + std::string("::") + value;
    return key;
  }

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
      return i->create(value);
    return field_ptr();
  }

  field_ptr fixfactory_t::field(const int& tag, const std::string& value) {
    if(const auto i = field_info_by(tag))
      return i->create(value);
    return field_ptr();
  }

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

} /* namespace ff */
