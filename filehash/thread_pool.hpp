#pragma once

#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>

namespace tools {

  template< unsigned int N >
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
        for(unsigned int i = 0; i < N; ++i)
          m_threads[ i ] = std::move(std::thread([&](){thread_routine();}));
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
        m_queue.add(value);
        m_cv.notify_one();
      }
    }

  public:

    exception_notice_t m_exception_notice;
    thread_notice_t m_thread_started;
    thread_notice_t m_thread_finished;
    thread_exception_notice_t m_thread_exception_notice;

  public:

    static const unsigned int  thread_count = N;

  private:

    typedef cache_queue<function_t> storage_t;

  private:

    void thread_routine() {
      try {
        thread_started(std::this_thread::get_id());
        storage_t::value_t f;
        while (!m_queue.empty() || !m_stop) {
          {
            std::unique_lock<std::mutex> _(m_mtx);
            while (!m_stop && m_queue.empty())
              m_cv.wait(_);
            if (m_queue.empty())
              continue;
            f.swap(m_queue.front());
            m_queue.store_front();
          }
          if (f)
            execute_internal(f);
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
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_threads[ N ];

  private:

    static const std::string error;
    static const std::string unknown_error;

  };

  template< unsigned int N >
  const std::string thread_pool<N>::error = " error: ";

  template< unsigned int N >
  const std::string thread_pool<N>::unknown_error = " unknown error.";

}; /* namespace tools */
