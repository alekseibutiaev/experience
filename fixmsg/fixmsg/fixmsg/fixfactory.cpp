#include <algorithm>

#include <quickfix/Group.h>
#include <quickfix/Session.h>
#include <quickfix/FixFields.h>

#include "fixfactory.h"

namespace {

  std::string gen_key(const FIX::SessionID& sid, const std::string& value) {
    const std::string& verid = FIX::Message::toApplVerID(sid.getBeginString());
    const std::string key = verid + std::string("::") + value;
    return key;
  }

} /* namespace */

namespace ff {

  field_ptr fixfactory_t::field(const std::string& name, const std::string& value) {
    auto it = m_field_map.find(name);
    return it == m_field_map.end() ? field_ptr() : it->second(value);
  }

  group_ptr fixfactory_t::group(const FIX::SessionID& sid, const std::string& value) {
    const auto it = m_group_map.find(gen_key(sid, value));
    return it == m_group_map.end() ? group_ptr() : it->second();
  }

  fixfactory_t::group_range_t fixfactory_t::group_range(const FIX::SessionID& sid, const std::string& value) {
    using value_t = group_map_t::value_type;
    const value_t key = value_t(gen_key(sid, value), 0);
    auto lower = std::lower_bound(m_group_map.begin(), m_group_map.end(), key, [](const value_t& lv, const value_t& rv) {
      const std::string sl = lv.first.substr(0, std::min(lv.first.size(), rv.first.size()));
      return sl < rv.first;
    });
    auto upper = std::upper_bound(m_group_map.begin(), m_group_map.end(), key, [](const value_t& lv, const value_t& rv) {
      const std::string sr = rv.first.substr(0, std::min(rv.first.size(), lv.first.size()));
      return lv.first < sr;
    });
    return group_range_t(lower, upper);
  }

  message_ptr fixfactory_t::message(const FIX::SessionID& sid, const std::string& value) {
    const auto it = m_message_map.find(gen_key(sid, value));
    return it == m_message_map.end() ? message_ptr() : it->second();
  }

} /* namespace ff */
