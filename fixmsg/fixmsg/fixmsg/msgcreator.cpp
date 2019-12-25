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
  std::string group_name(const ff::group_stack_t& stack, const std::string& name, const std::size_t depth) {
    std::ostringstream oss;
    for(std::size_t i = 0; i < depth; ++i)
      oss << stack[i] << "::";
    oss << name;
    std::cout << oss.str() << std::endl;
    return oss.str();
  }

} /* namespace */

namespace ff {

  msgcreator_t::msgcreator_t(ff::message_ptr& msg, const FIX::SessionID& sid)
      : m_msg(msg)
      , m_sid(sid)
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
        if(m_msg = std::move(ff::fixfactory_t::message(m_sid, name))) {
          m_group_stack[depth()] = name;
          fill_attributes(node.attributes(), m_msg.get());
        }
      }
      else if(ff::group_ptr grp = ff::fixfactory_t::group(m_sid, group_name(m_group_stack, name, depth()))) {
        m_group_stack[depth()] = name;
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

  void message_crack(const FIX::Message& msg, field_notice_f fn) {
    //std::size_t depth;

  }

}; /* namespace ff */

