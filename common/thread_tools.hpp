#pragma once

#include <string>
#include <thread>

namespace tools {

  bool set_name(std::thread& thread, const std::string& name);
  bool get_name(std::thread& thread, std::string& name);

} /* namespace tools */
