#pragma once

namespace tools {

  class buffer_t {
  public:
    buffer_t(const std::size_t& capacity);
    ~buffer_t();
    const std::size_t& capacity() const;
    const std::size_t& size() const;
    void* data();
    const void* data() const;
    void set_data(const void* data, std::size_t& size);
  private:
    const std::size_t m_capacity;
    void* m_data;
    std::size_t m_size;
  };

} /* namespace tools */
