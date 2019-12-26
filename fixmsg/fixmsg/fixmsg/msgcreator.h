#pragma once

#include <vector>
#include <string>
#include <utility>
#include <functional>

#include <pugixml.hpp>

#include <quickfix/SessionID.h>
#include <quickfix/FieldMap.h>

#include "fixfactory.h"

namespace ff {

  using field_t = std::pair<std::string, std::string>;
  using field_notice_f = std::function<void(std::size_t, field_t)>;

  class msgcreator_t {
  public:
    msgcreator_t(ff::message_ptr& msg, const FIX::SessionID& sid);
  protected:
    void add_fild(const std::string& name, const std::string& value, FIX::FieldMap* map);
    bool is_set_msg(const FIX::Message& msg, const int tag);
    bool is_set(const FIX::FieldMap& map, const int tag);
  protected:
    using strings_t = std::vector<std::string>;
  protected:
    ff::message_ptr& m_msg;
    const FIX::SessionID& m_sid;
    const fixfactory_t::message_info_t* m_msg_info;
    strings_t m_group_stack;
  };

  class from_xml : msgcreator_t, public pugi::xml_tree_walker {
  public:
    from_xml(ff::message_ptr& msg, const FIX::SessionID& sid);
    bool for_each(pugi::xml_node& node);
  private:
    using attribute_t = pugi::xml_object_range<pugi::xml_attribute_iterator>;
  private:
    void fill_attributes(const attribute_t& attr, FIX::FieldMap* map);
  };

  class msg_tree_walker_t {
  public:
    virtual ~msg_tree_walker_t() = default;
    virtual void msg(const std::string& name) = 0;
    virtual void field(const std::string& name, const std::string& value) = 0;
    virtual void group(const std::string& name, const std::size_t& count) = 0;
    virtual void exit() = 0;
  };

  void message_crack(const FIX::Message& msg, ff::msg_tree_walker_t& walker);

}; /* namespace ff */
