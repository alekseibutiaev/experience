#pragma once

#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <functional>

#include <pugixml.hpp>

#include <quickfix/Group.h>
#include <quickfix/SessionID.h>
#include <quickfix/FieldMap.h>

#include "fixfactory.h"

namespace ff {

  using field_t = std::pair<std::string, std::string>;
  using field_notice_f = std::function<void(std::size_t, field_t)>;

  class msgcreator_t {
  public:
    using message_ptr = std::shared_ptr<FIX::Message>;
    using messages_t = std::vector<message_ptr>;
  public:
    msgcreator_t(messages_t& messages, const FIX::SessionID& sid);
  protected:
    void add_field(const std::string& name, const std::string& value, FIX::FieldMap* map);
    bool is_set_msg(const FIX::Message& msg, const int tag);
    bool is_set(const FIX::FieldMap& map, const int tag);
  protected:
    using strings_t = std::vector<std::string>;
  protected:
    messages_t& m_messages;
    const FIX::SessionID& m_sid;
    const fixfactory_t::message_info_t* m_msg_info;
  };

  class from_xml : msgcreator_t, public pugi::xml_tree_walker {
  public:
    using log_out_t = std::function<void(const std::string&)>;
  public:
    from_xml(msgcreator_t::messages_t& msg, const FIX::SessionID& sid, const log_out_t& lo = log_out_t());
    bool for_each(pugi::xml_node& node) override;
    bool end(pugi::xml_node& node) override;
  private:
    using field_map_ptr = std::shared_ptr<FIX::FieldMap>;
    using stack_element_t = std::pair<field_map_ptr, std::string>;
    using group_stack_t = std::vector<stack_element_t>;
  private:
    field_map_ptr create_map(const bool flag, const std::string& name);
    ff::strings_t path(const std::string& name);
    void read_stack(const std::size_t& _depth);
  private:
    group_stack_t m_group_stack;
    log_out_t m_lo;
  };

  class from_text : msgcreator_t {
  public:
    from_text(msgcreator_t::messages_t& messages, const FIX::SessionID& sid);
    ~from_text();
    void operator()(const std::pair<std::string, std::string>& value);
  private:
    FIX::Message* m_msg;
  };

  class msg_tree_walker_t {
  public:
    enum field_type_t {
      e_string,
      e_char,
      e_double,
      e_int,
      e_bool,
      e_utc_time_stamp,
      e_utc_date,
      e_utc_time_only,
      e_check_sum
    };
  public:
    virtual ~msg_tree_walker_t() = default;
    virtual void msg(const std::string& name) = 0;
    virtual void field(const std::string& name, const std::string& value,
      const bool& obj, const field_type_t& type) = 0;
    virtual void group(const std::string& name, const std::size_t& count) = 0;
    virtual void exit(const std::string& name) = 0;
  };

  void message_crack(const FIX::Message& msg, ff::msg_tree_walker_t& walker);

}; /* namespace ff */
