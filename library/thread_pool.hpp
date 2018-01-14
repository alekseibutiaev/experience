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

  public:

    virtual ~thread_pool(){
      stop();
    }

    void start(){
      try {
        _stop = false;
        for(unsigned int i = 0; i < N; ++i)
          threads[ i ] = std::move(std::thread([&](){thread_routine();}));
        return;
      }
      catch(const std::exception& e){
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch(...){
        prepare_exception(__FUNCTION__ + unknown_error);
      }
      stop();
      pool_exception();
    }

    void start_only_existing_task(){
      try {
        m_stop = true;
        for(unsigned int i = 0; i < N; ++i){
          waiter w;
          m_threads[i] = std::move(std::thread([&](){
            w.notify();
            thread_routine();
          }));
          w.wait();
        }
        join();
        return;
      }
      catch(const std::exception& e){
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch(...){
        prepare_exception(__FUNCTION__ + std::string(" unknown error."));
      }
      stop();
      pool_exception();
    }


    void stop(){
      if(!m_stop){
        {
          std::unique_lock<std::mutex> _(m_mtx);
          m_stop = true;
          m_cv.notify_all();
        }
        join();
      }
   }

    void execute(function_t value){
      std::unique_lock<std::mutex> _(m_mtx);
      if(!m_stop){
        m_queue.add(value);
        m_cv.notify_one();
      }
    }

    virtual void prepare_exception(const std::string&){
    }

    virtual void thread_started(const std::thread::id&) {
    }

    virtual void thread_finished(const std::thread::id&) {
    }

    virtual void thread_finished(const std::thread::id&, const std::exception&) {
    }

  public:

    static const unsigned int  thread_count = N;

  private:

    typedef cache_queue<function_t> storage_t;

    class waiter {

    public:

      void notify(){
        std::lock_guard<std::mutex> _(m_mtx);
        m_flag = false;
        m_cv.notify_one();
      }

      void wait(){
        std::unique_lock<std::mutex> _(m_mtx);
        while(m_flag)
          m_cv.wait(_);
      }

      const bool flag()const{
        return m_flag;
      }

    private:

      bool m_flag = true;
      std::mutex m_mtx;
      std::condition_variable m_cv;

    };

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

    void execute_internal(function_t value){
      try {
        value();
      }
      catch(const std::exception& e){
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch(...){
        prepare_exception(__FUNCTION__ + unknown_error);
      }
    }

    void join(){
      for(unsigned int i = 0; i < N; ++i)
        if(m_threads[i].joinable())
          m_threads[i].join();
    }

    static void pool_exception(){
      static std::runtime_error re("thread_pool exception.");
      throw(re);
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
