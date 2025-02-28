#pragma once

#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>

#include "cache_queue.hpp"

namespace tools {

  template< std::size_t N >
  class thread_pool_t {

  public:

    using function_t = std::function<void()>;
    using execute_t = std::function<void(function_t)>;
    using idle_notice_t = std::function<void(const std::size_t&, const execute_t&)>;
    using exception_notice_t = std::function<void(const std::string&)>;
    using thread_notice_t = std::function<void(const std::thread::id&)>;
    using thread_exception_notice_t = std::function<void(const std::thread::id&, const std::exception&)>;

  public:

    thread_pool_t(std::size_t cash_deep = 0)
      : m_queue(cash_deep) {
    }

    virtual ~thread_pool_t() {
      stop();
    }

    void start() {
      try {
        m_stop = false;
        m_execute_int = std::bind(&thread_pool_t<N>::execute_int, this, std::placeholders::_1);
        select_empty(m_idle_notice);
        for(std::size_t i = 0; i < N; ++i)
          m_threads[ i ] = std::move(std::thread(&thread_pool_t<N>::thread_routine, this, i));
        return;
      }
      catch(const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch(...) {
        prepare_exception(__FUNCTION__ + unknown_error);
      }
      stop();
      pool_exception();
    }

    void stop() {
      if(!m_stop) {
        {
          std::lock_guard _(m_mtx);
          m_stop = true;
          m_cv.notify_all();
        }
        join();
      }
   }

    void execute(function_t value) {
      std::lock_guard _(m_mtx);
      if(!m_stop) {
        m_queue.push(std::move(value));
        m_cv.notify_one();
      }
    }

#if defined QUEUE_DEEP
    std::size_t queue_deep() {
      return m_queue.deep();
    }
#endif /* QUEUE_DEEP */

  public:

    idle_notice_t m_idle_notice;
    exception_notice_t m_exception_notice;
    thread_notice_t m_thread_started;
    thread_notice_t m_thread_finished;
    thread_exception_notice_t m_thread_exception_notice;

  public:

    static const std::size_t thread_count = N;

  private:

    using checkit_t = const bool&(thread_pool_t<N>::*)(const std::size_t&);
    using storage_t = cache_queue<function_t>;

  private:

    void execute_int(function_t value) {
      if(!m_stop) {
        m_queue.push(std::move(value));
        m_cv.notify_one();
      }
    }

    void select_empty(const idle_notice_t& value) {
      m_empty = value ? &thread_pool_t<N>::idle_detect : &thread_pool_t<N>::queue_check;
    }

    const bool& queue_check(const std::size_t& idx) {
      return m_wait[idx] = m_queue.empty();
    }

    const bool& idle_detect(const std::size_t& idx) {
      if((m_wait[idx] = m_queue.empty()) && (thread_count == std::count(std::begin(m_wait),
            std::end(m_wait), true)))
        m_idle_notice(idx, std::ref(m_execute_int));
      return m_wait[idx];
    }

    void thread_routine(const std::size_t idx) {
      try {
        thread_started(std::this_thread::get_id());
        storage_t::value_t f;
        const auto& empty = queue_check(idx);
        while(!m_stop || !empty) {
          {
            std::unique_lock _(m_mtx);
            m_cv.wait(_, [&]{return m_stop || !(this->*m_empty)(idx);});
            if(empty)
              continue;
            f = std::move(m_queue.front());
            m_queue.pop();
          }
          execute_internal(std::move(f));
        }
        thread_finished(std::this_thread::get_id());
      }
      catch(const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
        thread_finished(std::this_thread::get_id(), e);
      }
      catch(...) {
        prepare_exception(__FUNCTION__ + unknown_error);
        thread_finished(std::this_thread::get_id(), std::runtime_error(unknown_error));
      }
    }

    void execute_internal(function_t value) {
      try {
        value();
      }
      catch(const std::exception& e) {
        prepare_exception( __FUNCTION__ + error + e.what() );
      }
      catch(...) {
        prepare_exception ( __FUNCTION__ + unknown_error );
      }
    }

    void join() {
      for(unsigned int i = 0; i < N; ++i)
        if(m_threads[i].joinable())
          m_threads[i].join();
    }

    static void pool_exception() {
      static std::runtime_error re("thread_pool exception.");
      throw(re);
    }

    void prepare_exception(const std::string& value) {
      if(m_exception_notice)
        m_exception_notice(value);
    }

    void thread_started(const std::thread::id& value) {
      if(m_thread_started)
        m_thread_started(value);
    }

    void thread_finished(const std::thread::id& value) {
      if(m_thread_finished)
        m_thread_finished(value);
    }

    void thread_finished(const std::thread::id& id, const std::exception& exc) {
      if(m_thread_exception_notice)
        m_thread_exception_notice(id, exc);
    }

  private:

    bool m_stop = false;
    bool m_wait[ N ] = { false };
    execute_t m_execute_int;
    checkit_t m_empty;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_threads[ N ];

  private:

    static const std::string error;
    static const std::string unknown_error;

  };

  template< std::size_t N >
  const std::string thread_pool_t<N>::error = " error: ";

  template< std::size_t N >
  const std::string thread_pool_t<N>::unknown_error = " unknown error.";

}; /* namespace tools */
