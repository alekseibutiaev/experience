#include <cassert>
#include <cstdlib>
#include <cstring>
#include "buffer.hpp"

namespace tools {

  buffer_t::buffer_t(const std::size_t& capacity)
      : m_capacity(capacity)
      , m_data(malloc(m_capacity))
      , m_size(0) {
  }

  buffer_t::~buffer_t() {
    free(m_data);
  }

  const std::size_t& buffer_t::capacity() const {
    return m_capacity;
  }

  const std::size_t& buffer_t::size() const {
    return m_size;
  }

  void* buffer_t::data() {
    return m_data;
  }

  const void* buffer_t::data() const {
    return m_data;
  }

  void buffer_t::set_data(const void* data, std::size_t& size) {
    assert(size <= m_capacity);
    std::memcpy(m_data, data, size);
  }

} /* namespace tools */
