#include <set>
#include <limits>
#include "message.h"
#include "error.h"

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

  sequence_manager_t::sequence_manager_t(const execute_t& executer,
      const msg_consumer_t& consumer, error_t& error)
    : m_executer(executer)
    , m_consumer(consumer)
    , m_error(error)
    , m_sequence(std::numeric_limits<long>::min())
    , m_in_process(false) {
  }

  void sequence_manager_t::push(message_ptr&& value) {
#if 1
{
  std::ostringstream oss;
  oss << "[" << std::setw(8) << std::setfill('0') << value->sn() << "]s";
  m_error.debug(oss.str());
}
#endif
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
    std::set<message_t::messages_sequence_t*> mss;
    while(!tmp.empty()) {
#if 0
std::ostringstream oss;
oss << "o: [" << std::setw(8) << tmp.front()->sn() << "]";
m_error.debug(oss.str());
      auto& ms = tmp.front()->sequence_list();
      mss.insert(&ms);
      messages_t tmp1;
      tmp1.splice(tmp1.begin(), tmp, tmp.begin());
      ms.first.merge(tmp1, msg_cmp_t());
#endif
    }
#if 0
    for(auto i : mss) {
      std::size_t& sn = i->second;
      message_t::messages_t& mess = i->first;
      auto it = mess.begin();
      for(; it != mess.end(); ++it) {
        if((*it)->sn() > sn)
          break;
        else
          ++sn;
      }
      tmp.clear();
      tmp.splice(tmp.end(), std::move(mess), mess.begin(), it);
      m_executer([msgd = std::move(tmp), this]() mutable {
        m_consumer(msgd);}
      );
    }
#endif
#if 0
    tmp.sort(msg_cmp_t());
    m_messages.merge(std::move(tmp), msg_cmp_t());
    auto it = m_messages.begin();
    for(; it != m_messages.end(); ++it) {
      auto i = (*it)->sequence();
      if(i/*(*it)->sequence()*/ > m_sequence)
        break;
      else
        ++m_sequence;
    }
    tmp.splice(tmp.end(), std::move(m_messages), m_messages.begin(), it);
    m_executer([msgd = std::move(tmp), this]() mutable {
      m_consumer(msgd);}
    );
#endif
    tmp.clear();
    {
      std::lock_guard _(m_lock);
      m_in_process  = !m_input_messages.empty();
      if(m_in_process)
        m_executer(std::bind(&sequence_manager_t::process, this));
    }
  }

} /* namespace nasdaq */
