#include "message.h"

#include "sequence_manager.h"

namespace {

  struct msg_cmp_t {
    bool operator()(const nasdaq::sequence_manager_t::messages_t::value_type& lv,
        const nasdaq::sequence_manager_t::messages_t::value_type& rv) {
      return lv->sn() < rv->sn();
    }
  };

} /* namespace */

namespace nasdaq {

  sequence_manager_t::sequence_manager_t(const execute_t& executer, const msg_consumer_t& consumer)
    : m_executer(executer)
    , m_consumer(consumer)
    , m_sn(0)
    , m_in_process(false) {
  }

  void sequence_manager_t::push(message_ptr&& value) {
    std::lock_guard _(m_lock);
    m_input_messages.emplace_back(std::move(value));
    if(!m_in_process)
      m_executer(std::bind(&sequence_manager_t::process, this));
    m_in_process = true;
  }

  void sequence_manager_t::process() {
    messages_t tmp;
    {
      std::lock_guard _(m_lock);
      tmp = std::move(m_input_messages);
    }
    tmp.sort(msg_cmp_t());
    m_messages.merge(std::move(tmp), msg_cmp_t());
    auto it = m_messages.begin();
    for(; it != m_messages.end(); ++it)
      if((*it)->sn() > m_sn)
        break;
      else
        ++m_sn;
    tmp.splice(tmp.end(), std::move(m_messages), m_messages.begin(), it);
    m_executer([msgd = std::move(tmp), this]() mutable { m_consumer(msgd);});
    {
      std::lock_guard _(m_lock);
      if(!m_input_messages.empty())
        m_executer(std::bind(&sequence_manager_t::process, this));
      else
        m_in_process = false;
    }
  }

} /* namespace nasdaq */
