#include <mutex>
#include <fstream>

#include "table_manager.h"

namespace nasdaq {

  void table_manager_t::table(const std::string& stream, const std::string& msg, const fields_t& fields) {
    std::unique_lock _(m_lock_stream_msg);
    m_stream_msg[stream][msg] = fields;
  }

  const fields_t& table_manager_t::get_fields(const std::string& stream, const std::string& msg) const {
    static const fields_t empty;
    std::shared_lock _(m_lock_stream_msg);
    auto it1 = m_stream_msg.find(stream);
    if(it1 == m_stream_msg.end())
      return empty;
    auto it2 = it1->second.find(msg);
    if(it2 == it1->second.end())
      return empty;
    return it2->second;
  }

  bool table_manager_t::save(const std::string& file, const std::string& schema) {
    std::ofstream ofs(file);
    const bool res = static_cast<bool>(ofs);
    if(res)
      ofs << schema;
    return res;
  }

  std::string table_manager_t::load(const std::string& file) {
    std::string res;
    std::ifstream ifs(file);
    while(ifs)
      res += [](std::istream& is){std::string tmp; is >> tmp; return tmp;}(ifs);
    return res;
  }

} /* namespace nasdaq */
