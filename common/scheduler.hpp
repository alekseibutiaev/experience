#pragma once

#include <list>
#include <mutex>
#include <thread>
#include <chrono>
#include <utility>
#include <functional>
#include <condition_variable>

#include "commontypes.hpp"

namespace tools {

  using duration_t = std::chrono::system_clock::duration;
  using time_point_t = std::chrono::system_clock::time_point;
  using func_time_t = std::pair<time_point_t, function_t>;
  using alarm_list_t = std::list<func_time_t>;

  class scheduler_t {
  public:
    scheduler_t();
    ~scheduler_t();
    void start();
    void stop();
    void after(const duration_t& after, function_t& func);
    void at_time(const time_point_t& at, function_t& func);
    void set_executer(executor_t executor);
  private:
    void process();
    void executor(function_t func);
  private:
    bool m_stop;
    executor_t m_executor;
    alarm_list_t m_list;
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
  };

} /* namespace tools */
