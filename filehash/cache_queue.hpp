#pragma once

#include <list>

namespace tools {

  template< typename type_t >
  class cache_queue {

  public:

    typedef type_t value_t;
    typedef std::list<type_t> queue_t;

  public:

    void add(const type_t& value) {
      if(!m_cache_node.empty()) {
        m_queue.splice(m_queue.end(), m_cache_node, m_cache_node.begin());
        m_queue.back() = value;
      }
      else
        m_queue.push_back(value);
    }

    type_t& front() {
      return m_queue.front();
    }

    void store_front() {
      m_cache_node.splice(m_cache_node.end(), m_queue, m_queue.begin());
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

  private:

    queue_t m_queue;
    queue_t m_cache_node;

  };

} /* namespace tools */
