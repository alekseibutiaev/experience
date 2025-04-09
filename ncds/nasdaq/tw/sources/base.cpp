#include "../tw_visitor.h"
#include "base.h"


namespace nasdaq {

  namespace tw {

    base_t::messages_sequence_ptr base_t::m_messages;

    base_t::base_t(const message_t& value) : message_t(value) {
      if(!m_messages) {
        m_messages = std::make_shared<messages_sequence_t>();
        m_topics_msg.push_back(m_messages);
      }
    }

    const std::string& base_t::topic() const {
      static const std::string res = "TOTALVIEW";
      return res;
    }

    const long& base_t::sequence() const {
      return std::get<long>(m_values[e_sequence]);
    }

    message_t::messages_sequence_t& base_t::sequence_list() const {
      return *m_messages;
    }

  } /* namespace tw */

} /* namespace nasdaq */