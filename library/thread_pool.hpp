#pragma once

#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>

#include "cache_queue.hpp"

namespace tools {

  template< std::size_t N >
  class thread_pool {

  public:

    using function_t = std::function<void()>;
    using exception_notice_t = std::function<void(const std::string&)>;
    using thread_notice_t = std::function<void(const std::thread::id&)>;
    using thread_exception_notice_t = std::function<void(const std::thread::id&, const std::exception&)>;

  public:

    virtual ~thread_pool() {
      stop();
    }

    void start() {
      try {
        m_stop = false;
        select_empty(m_idle_notice);
        for(std::size_t i = 0; i < N; ++i)
          m_threads[ i ] = std::move(std::thread(&thread_pool<N>::thread_routine, this, i));
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
          std::unique_lock<std::mutex> _(m_mtx);
          m_stop = true;
          m_cv.notify_all();
        }
        join();
      }
   }

    void execute(function_t value) {
      std::unique_lock<std::mutex> _(m_mtx);
      if(!m_stop){
        m_queue.push(std::move(value));
        m_cv.notify_one();
      }
    }

  public:

    function_t m_idle_notice;
    exception_notice_t m_exception_notice;
    thread_notice_t m_thread_started;
    thread_notice_t m_thread_finished;
    thread_exception_notice_t m_thread_exception_notice;

  public:

    static const std::size_t thread_count = N;

  private:

    using checkit_t = bool(thread_pool<N>::*)(const std::size_t&);
    using storage_t = cache_queue<function_t>;

  private:

    void select_empty(const function_t& value) {
      m_empty = value ? &thread_pool<N>::idle_detect : &thread_pool<N>::queue_check;
    }

    bool queue_check(const std::size_t& idx) {
      return m_wait[idx] = m_queue.empty();
    }

    bool idle_detect(const std::size_t& idx) {
      m_wait[idx] = m_queue.empty();
      std::size_t t = 0;
      if(thread_count == (t = std::count(std::begin(m_wait), std::end(m_wait), true)))
        m_idle_notice();
      return m_wait[idx];
    }

    void thread_routine(const std::size_t idx) {
      try {
        thread_started(std::this_thread::get_id());
        storage_t::value_t f;
        m_wait[idx] = (this->*m_empty)(idx);
        while (!m_wait[idx] || !m_stop) {
          {
            std::unique_lock<std::mutex> _(m_mtx);
            m_cv.wait(_, [&]{return !(!m_stop && (this->*m_empty)(idx));});
            if (m_wait[idx])
              continue;
            f = std::move(m_queue.front());
            m_queue.pop();
          }
          execute_internal(std::move(f));
        }
        thread_finished(std::this_thread::get_id());
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
        thread_finished(std::this_thread::get_id(), e);
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + unknown_error);
        thread_finished(std::this_thread::get_id(), std::runtime_error(unknown_error));
      }
    }

    void execute_internal(function_t value) {
      try {
        value();
      }
      catch(const std::exception& e){
        prepare_exception( __FUNCTION__ + error + e.what() );
      }
      catch(...){
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
      if( m_exception_notice )
        m_exception_notice(value);
    }

    void thread_started(const std::thread::id& value) {
      if( m_thread_started )
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
  const std::string thread_pool<N>::error = " error: ";

  template< std::size_t N >
  const std::string thread_pool<N>::unknown_error = " unknown error.";

}; /* namespace tools */
