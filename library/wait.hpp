#pragma once

#include <mutex>
#include <condition_variable>

namespace tools {

  class wait_t {
  public:
    void wait() {
      std::unique_lock _(m_mtx);
      m_wait = true;
      m_cv.wait(_,[this]{return m_wait;});
      return;
    }
    void notify() {
      std::lock_guard _(m_mtx);
      m_wait = false;
      m_cv.notify_one();
    }
  private:
    bool m_wait;
    std::mutex m_mtx;
    std::condition_variable m_cv;
  };

} /* namespace tools */


