#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "scheduler.hpp"

namespace {

  struct ft_less_t {
    bool operator()(const tools::func_time_t& l, const tools::func_time_t& r) const {
      return l.first < r.first;
    }
  };

  class alarms_t {
  public:
    using al_t = tools::alarm_list_t;
    using alit_t = al_t::const_iterator;
  public:
    alarms_t() {}
    alarms_t(al_t& list, alit_t from, alit_t to) {
      m_list.splice(m_list.end(), list, from, to);
    }
    alarms_t(alarms_t&&) = default;
    alarms_t(const alarms_t&) = default;
    alarms_t& operator=(alarms_t&&) = default;
    alarms_t& operator=(const alarms_t&) = default;
    void operator()() const {
      try {
        for(auto& i: m_list)
          i.second();
      }
      catch(const std::exception&) {
      }
      catch(...) {
      }
    }
  private:
    tools::alarm_list_t m_list;
  };

} /* namespace */

namespace tools {

  scheduler_t::scheduler_t()
    : m_stop(false)
    , m_executor(std::bind(&scheduler_t::executor, this, std::placeholders::_1)){
  } 

  scheduler_t::~scheduler_t() {
    stop();
  }

  void scheduler_t::start() {
    m_stop = false;
    m_thread = std::thread(std::bind(&scheduler_t::process, this));
  }

  void scheduler_t::stop() {
    if(m_thread.joinable()) {
      {
        std::lock_guard<std::mutex> _(m_mutex);
        m_stop = true;
        m_cv.notify_one();
      }
      m_thread.join();
    }
  }

  void scheduler_t::after(const duration_t& after, function_t& func) {
    at_time(std::chrono::system_clock::now() + after, func);
  }

  void scheduler_t::at_time(const time_point_t& at, function_t& func) {
    auto ft = std::make_pair(at, func);
    bool first;
    {
      std::lock_guard<std::mutex> _(m_mutex);
      auto it = std::upper_bound(m_list.begin(), m_list.end(), ft, ft_less_t());
      first = it == m_list.begin();
      m_list.emplace(it, ft);
    }
    if(first)
      m_cv.notify_one();
  }

  void scheduler_t::set_executer(executor_t executor) {
    std::lock_guard<std::mutex> _(m_mutex);
    m_executor = std::move(executor);
  }

  void scheduler_t::process() {
    try {
      alarms_t alarms;
      while(!m_stop) {
        {
          std::unique_lock<std::mutex> _(m_mutex);
          while(!m_stop && m_list.empty())
            m_cv.wait(_);
          if(std::cv_status::timeout == m_cv.wait_until(_, m_list.front().first)) {
            auto it = std::upper_bound(m_list.cbegin(), m_list.cend(), m_list.front(), ft_less_t());
            alarms = std::move(alarms_t(m_list, m_list.cbegin(), it));
          }
          else
            continue;
        }
        m_executor(alarms);
      }
    }
    catch(const std::exception& ) {
    }
    std::cout << __FUNCTION__ << std::endl;
  }

  void scheduler_t::executor(function_t func) {
    func();
  }

} /* namespace tools */
