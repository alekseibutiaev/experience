#include <fstream>
#include <libtzif.h>

namespace {

  std::unique_ptr<unsigned char[]> read_data(const std::string name) {
    std::ifstream ifs( name, std::ifstream::binary);
    if(!ifs.good())
      throw std::runtime_error("file: " + name + "not available");
    //->decltype(std::ifstream::tellg)
    const auto len = [&ifs](){
      ifs.seekg(0,std::ifstream::end);
      auto res = ifs.tellg();
      ifs.seekg(0);
      return res;
    }();
    std::unique_ptr<unsigned char[]> res(new unsigned char[len]);
    ifs.read(reinterpret_cast<char*>(res.get()), len);
    return res;
  }

} /* namespace */

namespace tzif {

  reader_t::reader_t(const std::string& name)
    : m_buf(std::move(read_data(name)))
    , m_data(reinterpret_cast<const data_t*>(res.get())) {
  }

  reader_t::ver_t reader_t::version() const {
    return ver_t::e_v1;
  }

} /* namespace lib */
