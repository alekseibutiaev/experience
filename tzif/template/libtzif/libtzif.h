#pragma once

#include <string>
#include <memory>

namespace tzif {

  class data_t;

  class reader_t {
  public:
    enum ver_t{ e_v1, e_v2, e_v3 };
  public:
    reader_t(const std::string& name);
    ver_t version() const;
  private:
    std::unique_ptr<unsigned char[]> m_buf;
    const data_t* m_data;
  };

} /* namespace lib */
