#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "msgcreator.h"

namespace {
/*
  bool msgcreator_t::is_set(const FIX::FieldMap& map, const int tag) {
    return map.isSetField(tag);
  }

  bool is_set(const ff::message_ptr& msg, const int tag) {
    return is_set(msg->getHeader(), tag) || is_set(msg->getTrailer(), tag) ||
      is_set(msg->isSetField, tag);
  }
*/

  ff::strings_t group_path(const ff::strings_t& stack, const std::size_t depth, const std::string& name) {
    auto end = stack.begin();
    std::advance(end, depth - 1);
    ff::strings_t res(stack.begin(), end);
    res.push_back(name);
    return res;
  }

  void int_message_crack(const FIX::FieldMap& map, ff::msg_tree_walker_t& walker,
      const ff::fixfactory_t::message_info_t* mi, ff::strings_t& path) {
    for(FIX::FieldMap::const_iterator it = map.begin(); it != map.end(); ++it) {
      if(auto i = ff::fixfactory_t::field_info_by(it->getTag())) {
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

  msgcreator_t::msgcreator_t(ff::message_ptr& msg, const FIX::SessionID& sid)
      : m_msg(msg)
      , m_sid(sid)
      , m_msg_info(0)
      , m_group_stack(10) {
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

  from_xml::from_xml(ff::message_ptr& msg, const FIX::SessionID& sid)
      : msgcreator_t(msg, sid) {
  }

  bool from_xml::for_each(pugi::xml_node& node) {
    const std::string& name = node.name();
    if(!name.empty()) {
      if(0 == depth()) {
        if(0 == (m_msg_info = fixfactory_t::message_info_name(m_sid, name))) {
          // error message;
          return false;
        }
        if(m_msg = std::move(m_msg_info->creator()))
          fill_attributes(node.attributes(), m_msg.get());
      }
      else if(ff::group_ptr grp = ff::fixfactory_t::group(m_msg_info, group_path(m_group_stack, depth(), name))) {
        m_group_stack[depth() - 1] = name;
        fill_attributes(node.attributes(), grp.get());
        m_msg->addGroup(*grp);
      }
    }
    return true;
  }

  void from_xml::fill_attributes(const attribute_t& attr, FIX::FieldMap* map) {
    for(auto v: attr)
      add_fild(v.name(), v.value(), map);
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

