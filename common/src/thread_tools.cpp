#include <pthread.h>

#include "thread_tools.hpp"

namespace tools {

  bool set_name(std::thread& thread, const std::string& name) {
    return 0 == pthread_setname_np(thread.native_handle(), name.c_str());
  }

  bool get_name(std::thread& thread, std::string& name) {
    const std::size_t size = 256;
    char buf[size];
    auto res = 0 == pthread_getname_np(thread.native_handle(), buf, size);
    if(res)
      name = buf;
    return res;
  }

} /* namespace tools */
