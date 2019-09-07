#include "logger.hpp"
#include "wait.h"

namespace tools {

  void wait_t::wait() {
    _debug("wait notification", endline);
    std::unique_lock<std::mutex> _(m_mtx);
    m_stop = false;
    while(!m_stop)
      m_cv.wait(_);
    _debug("wait stop", endline);
  }

  void wait_t::notification() {
    std::unique_lock<std::mutex> _(m_mtx);
    m_stop = true;
    m_cv.notify_one();
    _debug("catch notification", endline);
  }

} /* namespace tools */