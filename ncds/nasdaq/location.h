#pragma once

#include <cstring>
#include <string>

namespace {

  std::string get_locaton(const char* file, const std::size_t& line) {
    static std::string res;
    if(res.empty()) {
      const char* tmp = 0;
      res = std::string(" ./") + (0 != (tmp = std::strrchr(file, '/')) ? tmp + 1 : file);
    }
    return res + (std::string(":") + std::to_string(line) + " ");
  }

  #define __FILE_STR__ get_locaton(__FILE__, __LINE__)

} /* namespace */

