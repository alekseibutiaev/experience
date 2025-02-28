#pragma once

#include <list>
#if defined QUEUE_DEEP
#include <atomic>
#include <algorithm>
#endif /* QUEUE_DEEP */


namespace tools {

  template< typename type_t >
  class cache_queue {

  public:

    typedef type_t value_t;
    typedef std::list<type_t> queue_t;

  public:

    cache_queue(std::size_t deep = 0) {
      m_cache_node.resize(deep, value_t());
    }

    void push(const type_t& value) {
      if(!m_cache_node.empty()) {
        m_queue.splice(m_queue.end(), m_cache_node, m_cache_node.begin());
        m_queue.back() = value;
      }
      else
        m_queue.push_back(value);
#if defined QUEUE_DEEP
      m_max = std::max(static_cast<std::size_t>(m_max), ++m_deep);
#endif /* QUEUE_DEEP */
    }

    void push(type_t&& value) {
      if(!m_cache_node.empty()) {
        m_queue.splice(m_queue.end(), m_cache_node, m_cache_node.begin());
        m_queue.back() = std::move(value);
      }
      else
        m_queue.push_back(std::move(value));
#if defined QUEUE_DEEP
      m_max = std::max(static_cast<std::size_t>(m_max), ++m_deep);
#endif /* QUEUE_DEEP */
    }

    type_t& front() {
      return m_queue.front();
    }

    void pop() {
      m_cache_node.splice(m_cache_node.end(), m_queue, m_queue.begin());
#if defined QUEUE_DEEP
      --m_deep;
#endif /* QUEUE_DEEP */
    }

    bool empty() const {
      return m_queue.empty();
    }

    queue_t& data() {
      return m_queue;
    }

    void store_data(queue_t& value) {
      m_cache_node.splice(m_cache_node.end(), value);
    }
#if defined QUEUE_DEEP
    std::size_t deep() const {
      return m_max.exchange(0);
    }
#endif /* QUEUE_DEEP */

  private:

    queue_t m_queue;
    queue_t m_cache_node;
#if defined QUEUE_DEEP
    mutable std::atomic_size_t m_max = 0;
    std::atomic_size_t m_deep;
#endif /* QUEUE_DEEP */
    
  };

} /* namespace tools */
