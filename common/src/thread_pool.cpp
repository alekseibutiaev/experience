#include <iterator>
#include "thread_tools.hpp"
#include "thread_pool.hpp"

namespace tools {

  const std::string thread_pool_base_t::error = " error: ";

  const std::string thread_pool_base_t::unknown_error = " unknown error.";

  void thread_pool_base_t::name(const std::string& name) {
    m_name = name;
  }

  void thread_pool_base_t::execute(function_t value) {
    std::unique_lock<std::mutex> _(m_mtx);
    if(!m_stop){
      m_queue.add(value);
      m_cv.notify_one();
    }
  }

  void thread_pool_base_t::start(std::thread* begin, std::thread* end) {
    try {
      m_stop = false;
      for(std::thread* it = begin; it != end; ++it) {
        auto th = std::thread(std::bind(&thread_pool_base_t::thread_routine, this));
        if(!m_name.empty())
          set_name(th, m_name + std::to_string(std::distance(begin, it)));
        *it = std::move(th);
      }
      return;
    }
    catch(const std::exception& e) {
      prepare_exception(__FUNCTION__ + error + e.what());
    }
    catch(...) {
      prepare_exception(__FUNCTION__ + unknown_error);
    }
    stop(begin, end);
    pool_exception();
  }

  void thread_pool_base_t::stop(std::thread* begin, std::thread* end) {
    if(!m_stop) {
      {
        std::unique_lock<std::mutex> _(m_mtx);
        m_stop = true;
        m_cv.notify_all();
      }
      join(begin, end);
    }
  }

  void thread_pool_base_t::join(std::thread* begin, std::thread* end) {
    for(std::thread* it = begin; it != end; ++it)
      if(it->joinable())
        it->join();
  }

  void thread_pool_base_t::thread_routine() {
    try {
      thread_started(std::this_thread::get_id());
      storage_t::value_t f;
      while(!m_queue.empty() || !m_stop) {
        {
          std::unique_lock<std::mutex> _(m_mtx);
          while(!m_stop && m_queue.empty())
            m_cv.wait(_);
          if(m_queue.empty())
            continue;
          f = std::move(m_queue.front());
          m_queue.store_front();
        }
        if(f)
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

  void thread_pool_base_t::execute_internal(function_t value) {
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

  void thread_pool_base_t::prepare_exception(const std::string& value) {
    if(m_exception_notice)
      m_exception_notice(value);
  }

  void thread_pool_base_t::thread_started(const std::thread::id& value) {
    if(m_thread_started)
      m_thread_started(value);
  }

  void thread_pool_base_t::thread_finished(const std::thread::id& value) {
    if(m_thread_finished)
      m_thread_finished(value);
  }

  void thread_pool_base_t::thread_finished(const std::thread::id& id, const std::exception& exc) {
    if(m_thread_exception_notice)
      m_thread_exception_notice(id, exc);
  }

  void thread_pool_base_t::pool_exception() {
    static std::runtime_error re("thread_pool exception.");
    throw(re);
  }

} /* namespace tools */
