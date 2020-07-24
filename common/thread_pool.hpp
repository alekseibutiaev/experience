#pragma once

#include <mutex>
#include <thread>
#include <string>
#include <iterator>
#include <functional>
#include <condition_variable>

#include "tools.hpp"
#include "commontypes.hpp"
#include "cache_queue.hpp"

namespace tools {

  class thread_pool_base_t {
  protected:
    using exception_notice_t = std::function<void(const std::string&)>;
    using thread_notice_t = std::function<void(const std::thread::id&)>;
    using thread_exception_notice_t = std::function<void(const std::thread::id&, const std::exception&)>;
  protected:
    thread_pool_base_t() = default;
    ~thread_pool_base_t() = default;
    void name(const std::string& name);
    void execute(function_t value);
    void start(std::thread* begin, std::thread* end);
    void stop(std::thread* begin, std::thread* end);
    void join(std::thread* begin, std::thread* end);
  protected:
    exception_notice_t m_exception_notice;
    thread_notice_t m_thread_started;
    thread_notice_t m_thread_finished;
    thread_exception_notice_t m_thread_exception_notice;
  private:
    typedef cache_queue<function_t> storage_t;
  private:
    void thread_routine();
    void execute_internal(function_t value);
    void prepare_exception(const std::string& value);
    void thread_started(const std::thread::id& value);
    void thread_finished(const std::thread::id& value);
    void thread_finished(const std::thread::id& id, const std::exception& exc);
  private:
    static void pool_exception();
  private:
    bool m_stop = false;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::string m_name;
  private:
    static const std::string error;
    static const std::string unknown_error;
  };

  template<std::size_t N>
  class thread_pool_t : thread_pool_base_t {
  public:
    using exception_notice_t = thread_pool_base_t::exception_notice_t;
    using thread_notice_t = thread_pool_base_t::thread_notice_t;
    using thread_exception_notice_t = thread_pool_base_t::thread_exception_notice_t;
  public:
    virtual ~thread_pool_t() {
      stop();
    }
    using thread_pool_base_t::execute;
    using thread_pool_base_t::name;
    void start() {
      thread_pool_base_t::start(std::begin(m_threads), std::end(m_threads));
    }
    void stop() {
      thread_pool_base_t::stop(std::begin(m_threads), std::end(m_threads));
    }
  public:
    using thread_pool_base_t::m_exception_notice;
    using thread_pool_base_t::m_thread_started;
    using thread_pool_base_t::m_thread_finished;
    using thread_pool_base_t::m_thread_exception_notice;
  public:
    static const std::size_t thread_count = N;
  private:
    std::thread m_threads[N];
  };

}; /* namespace tools */
