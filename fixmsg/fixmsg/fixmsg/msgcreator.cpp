#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "msgcreator.h"

namespace {
/*
  ff::strings_t group_path(const ff::strings_t& stack, const std::size_t depth, const std::string& name) {
    auto end = stack.begin();
    std::advance(end, depth - 1);
    ff::strings_t res(stack.begin(), end);
    res.push_back(name);
    return res;
  }
*/
  void int_message_crack(const FIX::FieldMap& map, ff::msg_tree_walker_t& walker,
      const ff::fixfactory_t::message_info_t* mi, ff::strings_t& path) {
    for(FIX::FieldMap::const_iterator it = map.begin(); it != map.end(); ++it) {
      if(auto i = ff::fixfactory_t::field_info_by(it->getTag())) {
        if("NoNested2PartyIDs" == i->name)
          std::cout << std::endl;
        if(i->is_group) {
          const std::size_t count = std::stoull(it->getString());
          path.push_back(i->name);
          walker.group(i->name, count);
          if(ff::group_ptr group = ff::fixfactory_t::group(mi, path)) {
            for(std::size_t i = 0; i < count; ++i) {
              map.getGroup(i + 1, group->field(), *group);
              int_message_crack(*group, walker, mi, path);
              group->clear();
            }
          }
          path.pop_back();
          walker.exit();
        }
        else 
          walker.field(i->name, it->getString());
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

  void msgcreator_t::add_fild(const std::string& name, const std::string& value,
      FIX::FieldMap* map) {
    if(ff::field_ptr field = ff::fixfactory_t::field(name, value)) {
      if(FIX::Message* msg = dynamic_cast<FIX::Message*>(map)) {
        if(!is_set_msg(*msg, field->getTag()))
          msg->setField(*field);
      }
      else if(FIX::Group* grp = dynamic_cast<FIX::Group*>(map)) {
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

  from_xml::from_xml(msgcreator_t::messages_t& messages, const FIX::SessionID& sid)
      : msgcreator_t(messages, sid) {
  }

  bool from_xml::for_each(pugi::xml_node& node) {
    if(node.empty())
      return true;
    const std::string& name = node.name();
    read_stack(depth());
    const auto msg_info = m_msg_info;
    if(0 == msg_info && 0 == ((m_msg_info = fixfactory_t::message_info_name(m_sid, name)))) {
      // error message;
      return false;
    }
    if(from_xml::field_map_ptr map = create_map(0 != msg_info, name)) {
      fill_attributes(node.attributes(), map.get());
      m_group_stack.emplace_back(std::move(map), name);
      return true;
    }
    return false;
  }

  from_xml::field_map_ptr from_xml::create_map(const bool flag, const std::string& name) {
    if(flag)
      return ff::fixfactory_t::group(m_msg_info, path(name));
    return m_msg_info->creator();
  }

  bool from_xml::end(pugi::xml_node& node) {
    read_stack(0);
    return true;
  }

  void from_xml::fill_attributes(const attribute_t& attr, FIX::FieldMap* map) {
    for(auto v: attr)
      add_fild(v.name(), v.value(), map);
  }

  ff::strings_t from_xml::path(const std::string& name) {
    ff::strings_t res;
    for(int i = 1; i < depth(); ++i)
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
    if(auto mi = ff::fixfactory_t::message_info_name(msg, name)) {
      ff::strings_t group_path;
      walker.msg(fixfactory_t::msg_name(msg));
      int_message_crack(msg.getHeader(), walker, mi, group_path);
      int_message_crack(msg, walker, mi, group_path);
      int_message_crack(msg.getTrailer(), walker, mi, group_path);
      walker.exit();
    }
  }

}; /* namespace ff */

