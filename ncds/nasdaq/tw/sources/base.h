#pragma once

#include <string>
#include "../../message.h"
#include "../tw_types.h"

namespace nasdaq {

  namespace tw {

    class base_t : public message_t {
    public:
      enum { e_sequence = 1 };
    public:
      base_t(const message_t& value);
      const long& sequence() const override;
      const std::string& topic() const override;
      messages_sequence_t& sequence_list() const override;
    private:
      static messages_sequence_ptr m_messages;
    };

  } /* namespace tw */

} /* namespace nasdaq */