#include "logger.hpp"
#include "wait.h"

namespace tools {

  void wait_t::wait(const std::string& msg) {
    _info(msg, endline);
    std::unique_lock<std::mutex> _(m_mtx);
    m_stop = false;
    while(!m_stop)
      m_cv.wait(_);
  }

  void wait_t::notify(const std::string& msg) {
    std::unique_lock<std::mutex> _(m_mtx);
    m_stop = true;
    m_cv.notify_one();
    _info(msg, endline);
  }

} /* namespace tools */