#pragma once

#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>

namespace tools {

  template< unsigned int N >
  class thread_pool {
  public:

    typedef std::function<void()> function_t;

  public:

    thread_pool(){
    }

    virtual ~thread_pool(){
      stop();
    }

    void start(){
      try {
        _stop = false;
        for (unsigned int i = 0; i < N; ++i)
          threads[ i ] = std::move(std::thread([&](){thread_routine();}));
        return;
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + std::string(" error: ") + e.what());
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + std::string(" unknown error."));
      }
      stop();
      pool_exception();
    }

    void start_only_existing_task(){
      try {
        _stop = true;
        for (unsigned int i = 0; i < N; ++i)
          threads[ i ] = std::move(std::thread([&](){thread_routine();}));
        join();
        return;
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + std::string(" error: ") + e.what());
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + std::string(" unknown error."));
      }
      stop();
      pool_exception();
    }


    void stop() {
      if (!_stop) {
        {
          std::unique_lock<std::mutex> _(mtx);
          _stop = true;
          cv.notify_all();
        }
     }
   }

  void execute(function_t value) {
    std::unique_lock<std::mutex> _(mtx);
    if (!_stop) {
      queue.add( value );
      cv.notify_one();
    }
  }

  virtual void prepare_exception(const std::string& value){
    std::cerr << value << std::endl;
  }

  private:

    typedef cache_queue<function_t> storage_t;

  private:

    void thread_routine() {
      try {
        storage_t::value_t f;
        while(!queue.empty() || !_stop) {
          {
            std::unique_lock<std::mutex> _(mtx);
            while(!_stop && queue.empty())
              cv.wait(_);
            if(queue.empty())
              continue;
            f.swap(queue.front());
            queue.store_front();
         }
         if( f )
           execute_internal(f);
        }
     }
     catch( const std::exception& e ) {
       prepare_exception(__FUNCTION__ + std::string(" error: ") + e.what());
     }
  }

  void execute_internal(function_t value) {
    try {
      value();
    }
    catch (const std::exception& e) {
      prepare_exception(__FUNCTION__ + std::string(" error: ") + e.what());
    }
    catch (...) {
      prepare_exception(__FUNCTION__ + std::string(" unknown error."));
    }
  }

  void join() {
    for(unsigned int i = 0; i < N; ++i)
      if(threads[i].joinable())
        threads[i].join();
  }

  static void pool_exception() {
      static std::runtime_error re("thread_pool exception.");
      throw(re);
  }

  private:

   bool _stop = true;
   storage_t queue;
   std::mutex mtx;
   std::condition_variable cv;
   std::thread threads[ N ];

  };

}; /* namespace tools */

