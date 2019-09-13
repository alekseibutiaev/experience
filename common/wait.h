#pragma once

#include <mutex>
#include <string>
#include <condition_variable>

namespace tools {

  class wait_t {
  public:
    void wait(const std::string& msg = "wait notification");
    void notify(const std::string& msg = "notification");
  private:
    bool m_stop;
    std::mutex m_mtx;
    std::condition_variable m_cv;
  };

} /* namespace tools */