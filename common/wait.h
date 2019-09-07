#pragma once

#include <mutex>
#include <condition_variable>

namespace tools {

  class wait_t {
  public:
    void wait();
    void notification();
  private:
    bool m_stop;
    std::mutex m_mtx;
    std::condition_variable m_cv;
  };

} /* namespace tools */