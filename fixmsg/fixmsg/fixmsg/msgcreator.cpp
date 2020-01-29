#include <cassert>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>

#include <quickfix/Field.h>
#include <quickfix/Group.h>

#include "fixfactory.h"
#include "msgcreator.h"

#if 0

#include "Common.h"
#undef LOG_NAME
#define LOG_NAME "MFIX"
#define ENDL
#else
#define LOG_DEBUG std::cout
#define ENDL << std::endl
#endif

namespace {

  ff::msg_tree_walker_t::field_type_t get_type(const ff::field_uptr& value) {
    if(0 != dynamic_cast<const FIX::StringField*>(value.get()))
      return ff::msg_tree_walker_t::e_string;
    if(0 != dynamic_cast<const FIX::CharField*>(value.get()))
      return ff::msg_tree_walker_t::e_char;
    if(0 != dynamic_cast<const FIX::DoubleField*>(value.get()))
      return ff::msg_tree_walker_t::e_double;
    if(0 != dynamic_cast<const FIX::IntField*>(value.get()))
      return ff::msg_tree_walker_t::e_int;
    if(0 != dynamic_cast<const FIX::BoolField*>(value.get()))
      return ff::msg_tree_walker_t::e_bool;
    if(0 != dynamic_cast<const FIX::UtcTimeStampField*>(value.get()))
      return ff::msg_tree_walker_t::e_utc_time_stamp;
    if(0 != dynamic_cast<const FIX::UtcDateField*>(value.get()))
      return ff::msg_tree_walker_t::e_utc_date;
    if(0 != dynamic_cast<const FIX::UtcTimeOnlyField*>(value.get()))
      return ff::msg_tree_walker_t::e_utc_time_only;
    if(0 != dynamic_cast<const FIX::CheckSumField*>(value.get()))
      return ff::msg_tree_walker_t::e_check_sum;
    return ff::msg_tree_walker_t::e_string;
  }

  bool is_delimiter(const FIX::FieldMap& map, const int tag) {
    int tmp = -1;
    if(const FIX::Group* g = dynamic_cast<const FIX::Group*>(&map))
      tmp = g->delim();
    return tmp == -1 ? false : tmp == tag;
  }

  void int_message_crack(const FIX::FieldMap& map, ff::msg_tree_walker_t& walker,
      const ff::fixfactory_t::message_info_t* mi, ff::strings_t& path) {
    for(FIX::FieldMap::const_iterator it = map.begin(); it != map.end(); ++it) {
      if(auto i = ff::fixfactory_t::field_info_by(it->getTag())) {
        if(i->is_group) {
          const std::size_t count = std::stoull(it->getString());
          path.push_back(i->name);
          walker.group(i->name, count);
          if(auto group = ff::fixfactory_t::group(mi, path)) {
            for(std::size_t i = 0; i < count; ++i) {
              if(!map.hasGroup(i + 1, group->field())) {
                LOG_DEBUG << "not found group: " << i + 1 << group->field() ENDL;
                continue;
              }
              map.getGroup(i + 1, group->field(), *group);
              int_message_crack(*group, walker, mi, path);
              group->clear();
            }
          }
          path.pop_back();
          walker.exit(i->name);
        }
        else
          walker.field(i->name, it->getString(), is_delimiter(map, it->getTag()),
            get_type(i->creator(std::string())));
      }
    }
  }

} /* namespace */

namespace ff {

  msgcreator_t::msgcreator_t(messages_t& messages, const FIX::SessionID& sid)
      : m_messages(messages)
      , m_sid(sid)
      , m_msg_info(0) {
  }

  void msgcreator_t::add_field(const std::string& name, const std::string& value,
      FIX::FieldMap* map) {
    if(auto field = ff::fixfactory_t::field(name, value)) {
      if(auto msg = dynamic_cast<FIX::Message*>(map)) {
        if(!is_set_msg(*msg, field->getTag()))
          msg->setField(*field);
      }
      else if(auto grp = dynamic_cast<FIX::Group*>(map)) {
        grp->setField(*field);
      }
      else { /* error message */ }
      return;
    }
    // error message
  }

  bool msgcreator_t::is_set_msg(const FIX::Message& msg, const int tag) {
    return is_set(msg.getHeader(), tag) || is_set(msg.getTrailer(), tag) ||
      is_set(msg, tag);
  }

  bool msgcreator_t::is_set(const FIX::FieldMap& map, const int tag) {
    return map.isSetField(tag);
  }

  from_xml::from_xml(msgcreator_t::messages_t& messages, const FIX::SessionID& sid, const from_xml::log_out_t& lo)
      : msgcreator_t(messages, sid)
      , m_lo(lo) {
  }

  bool from_xml::for_each(pugi::xml_node& node) {
    if(node.empty())
      return true;
    const std::string& name = node.name();
    read_stack(depth());
    const auto mi = m_msg_info;
    if(0 == mi && 0 == (m_msg_info = fixfactory_t::message_info_name(m_sid, name))) {
      m_lo("can`t open message: " + name);
      return false;
    }
    if(auto map = create_map(0 != mi, name)) {
      for(auto a : node.attributes())
        add_field(a.name(), a.value(), map.get());
      m_group_stack.emplace_back(std::move(map), name);
      return true;
    }
    m_lo("can`t create group: " + name);
    return false;
  }

  from_xml::field_map_ptr from_xml::create_map(const bool flag, const std::string& name) {
    assert(0 != m_msg_info);
    if(flag)
      return ff::fixfactory_t::group(m_msg_info, path(name));
    return m_msg_info->creator();
  }

  bool from_xml::end(pugi::xml_node&) {
    read_stack(0);
    return true;
  }

  ff::strings_t from_xml::path(const std::string& name) {
    ff::strings_t res;
    for(std::size_t i = 1; i < m_group_stack.size(); ++i)
      res.push_back(m_group_stack[i].second);
    res.push_back(name);
    return res;
  }

  void from_xml::read_stack(const std::size_t& _depth) {
    while(_depth < m_group_stack.size()) {
      stack_element_t element = m_group_stack.back();
      m_group_stack.pop_back();
      if(!m_group_stack.empty()) {
        FIX::Group* grp = static_cast<FIX::Group*>(element.first.get());
        m_group_stack.back().first->addGroup(grp->field(), *grp);
      }
      else {
        m_messages.emplace_back(std::static_pointer_cast<FIX::Message>(element.first));
        m_msg_info = 0;
      }
    }
  }

  void message_crack(const FIX::Message& msg, msg_tree_walker_t& walker) {
    const std::string name = fixfactory_t::msg_name(msg);
    if(name.empty())
      return;
    try {
      if(auto mi = ff::fixfactory_t::message_info_name(msg, name)) {
        ff::strings_t group_path;
        walker.msg(name);
        int_message_crack(msg.getHeader(), walker, mi, group_path);
        int_message_crack(msg, walker, mi, group_path);
        int_message_crack(msg.getTrailer(), walker, mi, group_path);
        walker.exit(name);
      }
    }
    catch(const FIX::Exception& e) {
      LOG_DEBUG << e.what();
    }
  }

  from_text::from_text(msgcreator_t::messages_t& messages, const FIX::SessionID& sid)
      : msgcreator_t(messages, sid)
      , m_msg(0) {
  }

  from_text::~from_text() {
  }

  void from_text::operator()(const std::pair<std::string, std::string>& value) {
    if(0 == m_msg) {
      message_uptr msg;
      if((msg = std::move(ff::fixfactory_t::message_name(m_sid, value.first))) ||
          (msg = std::move(ff::fixfactory_t::message_type(m_sid, value.first)))) {
        m_messages.emplace_back(std::move(msg));
        m_msg = m_messages.back().get();
      }
    }
    else if(ff::field_uptr f = ff::fixfactory_t::field(value.first, value.second)) {
      if(!is_set_msg(*m_msg, f->getTag()))
        m_msg->setField(*f);
    }
  }

}; /* namespace ff */
