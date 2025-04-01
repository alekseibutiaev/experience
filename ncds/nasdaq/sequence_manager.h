#pragma once

#include <list>
#include <mutex>
#include <functional>

#include "types.h"

namespace nasdaq {

  class sequence_manager_t {
  public:
    using messages_t = std::list<message_ptr>;
    using msg_consumer_t = std::function<void(messages_t&)>;
  public:
    sequence_manager_t(const execute_t& executer, const msg_consumer_t& consumer);
    void push(message_ptr&& value);
  private:
    void process();
  private:
    const execute_t m_executer;
    const msg_consumer_t m_consumer;
    long m_sequence;
    bool m_in_process;
    std::mutex m_lock;
    messages_t m_input_messages;
    messages_t m_messages;
  };

} /* namespace nasdaq */
