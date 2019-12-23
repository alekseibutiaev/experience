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
  std::string group_name(const ff::group_stack_t& stack, const std::string& name) {
    std::ostringstream oss;
    for(const auto& i : stack)
      oss << i.first << "::";
    oss << name;
    std::cout << oss.str() << std::endl;
    return oss.str();
  }


} /* namespace */

namespace ff {

  msgcreator_t::msgcreator_t(ff::message_ptr& msg, const FIX::SessionID& sid)
      : m_msg(msg)
      , m_sid(sid) {
  }

  void msgcreator_t::add_fild(const std::string& name, const std::string& value) {
    if(ff::field_ptr field = ff::fixfactory_t::field(name, value)) {
      FIX::FieldMap* fm = m_group_stack.back().second;
      if(FIX::Message* msg = dynamic_cast<FIX::Message*>(fm)) {
        if(!is_set(*msg, field->getTag()))
          msg->setField(*field);
      }
    }
  }

  bool msgcreator_t::is_set(const FIX::Message& msg, const int tag) {
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
    if(!m_msg) {
      if(m_msg = std::move(ff::fixfactory_t::message(m_sid, name)))
        m_group_stack.emplace_back(name, m_msg.get());
      fill_attributes(node.attributes());
    }
    else if(ff::group_ptr grp = ff::fixfactory_t::group(m_sid, group_name(m_group_stack, name))) {
      m_group_stack.emplace_back(name, grp.get());
      fill_attributes(node.attributes());
    }
    return true;
  }

  void from_xml::fill_attributes(const attribute_t& attr) {
    for(auto v: attr) {
      const std::string name = v.name();
      const std::string value = v.value();
      add_fild(name, value);
    }
  }


#if 0
  class fixcreator_t : public pugi::xml_tree_walker {
  public:
    fixcreator_t(ff::message_ptr& msg, const FIX::SessionID& sid)
        : m_msg(msg)
        , m_sid(sid) {
    }
    bool for_each(pugi::xml_node& node) {
      if(m_msg = std::move(ff::fixfactory_t::message(m_sid, node.name()))) {
        for(auto attr: node.attributes()) {
          if(ff::field_ptr f = ff::fixfactory_t::field(attr.name(), attr.value())) {
            if(!is_set(m_msg, f->getTag()))
              m_msg->setField(*f);
          }
          else
            LOG_WARNING << "unknown field: " << attr.name();
        }
      }
      else
        LOG_WARNING << "unknown message: " << m_sid.getBeginString() << "::" << node.name();
      return true;
    }
    void operator()(const std::pair<std::string, std::string>& value) {
      if(!m_msg && !(m_msg = std::move(ff::fixfactory_t::message(m_sid, value.first))))
        LOG_WARNING << "unknown field: " << value.first;
      else if(ff::field_ptr f = ff::fixfactory_t::field(value.first, value.second)) {
        if(!is_set(m_msg, f->getTag()))
          m_msg->setField(*f);
      }
    }
  private:
    inline bool is_set(const ff::message_ptr& msg, const int tag) {
      return msg->getHeader().isSetField(tag) || msg->getTrailer().isSetField(tag) || msg->isSetField(tag);
    }
  private:
    ff::message_ptr& m_msg;
    const FIX::SessionID& m_sid;
  };
#endif


}; /* namespace ff */

