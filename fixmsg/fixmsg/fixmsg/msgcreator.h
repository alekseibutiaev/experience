#pragma once

#include <list>
#include <string>
#include <utility>

#include <pugixml.hpp>

#include <quickfix/SessionID.h>
#include <quickfix/FieldMap.h>

#include "fixfactory.h"

namespace ff {

  using name_group_t = std::pair<std::string, FIX::FieldMap*>;
  using group_stack_t = std::list<name_group_t>;

  class msgcreator_t {
  public:
    msgcreator_t(ff::message_ptr& msg, const FIX::SessionID& sid);
    void add_fild(const std::string& name, const std::string& value);
  protected:
    bool is_set(const FIX::Message& msg, const int tag);
    bool is_set(const FIX::FieldMap& map, const int tag);
  protected:
    ff::message_ptr& m_msg;
    const FIX::SessionID& m_sid;
    group_stack_t m_group_stack;
  };

  class from_xml : msgcreator_t, public pugi::xml_tree_walker {
  public:
    from_xml(ff::message_ptr& msg, const FIX::SessionID& sid);
    bool for_each(pugi::xml_node& node);
  private:
    using attribute_t = pugi::xml_object_range<pugi::xml_attribute_iterator>;
  private:
    void fill_attributes(const attribute_t& attr);
  };

/*
    bool for_each(pugi::xml_node& node);
    void operator()(const std::pair<std::string, std::string>& value);
*/

}; /* namespace ff */
