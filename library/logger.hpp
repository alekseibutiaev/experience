#pragma once

#include <mutex>
#include <thread>
#include <memory>
#include <sstream>
#include <iterator>
#include <iostream>
#include <condition_variable>

#include "cache_queue.hpp"

namespace tools {

  class logger {

  public:

  logger()
      : m_stop(false)
      , m_th([&]() {out_tread();}) {
  }

  ~logger() {
    stop();
  }

   void stop() {
    if(m_th.joinable()) {
      {
        std::unique_lock<std::mutex> _(m_mtx);
        m_stop = true;
        m_cv.notify_one();
      }
      m_th.join();
    }
  }

    template <typename type1_t, typename... types_t >
      static void out(const type1_t& value, const types_t&... values) {
      std::stringstream stream;
      stream << value;
      out(stream, values...);
    }

  public:

    static const char endl;

  private:

    typedef cache_queue<std::string> storage_t;

  private:

    void out_int(const std::string& value) {
      std::unique_lock<std::mutex> _(m_mtx);
      m_queue.add(value);
      m_cv.notify_one();
    }

    void out_tread() {
      try {
        storage_t::queue_t local;
        while(!m_stop || !m_queue.empty()) {
          {
            std::unique_lock<std::mutex> _(m_mtx);
            while(!m_stop && m_queue.empty())
              m_cv.wait(_);
            local.swap(m_queue.data());
          }
          std::copy(local.begin(), local.end(), std::ostream_iterator<std::string>(std::cout));
          std::unique_lock<std::mutex> _(m_mtx);
          m_queue.store_data(local);
        }
      }
      catch(const std::exception& e) {
        std::cerr << e.what()<< std::endl;
      }
  }

  static void out(std::stringstream& stream) {
    if(!mylog)
      mylog.reset(new logger());
      mylog->out_int(stream.str());
  }

  template <typename type1_t, typename... types_t >
  static void out(std::stringstream& stream, const type1_t& value, const types_t&... values) {
    stream << value;
    out(stream, values...);
  }

  private:

    bool m_stop;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_th;

  private:

    static std::unique_ptr<logger> mylog;

  };

  const char logger::endl = '\n';
  std::unique_ptr<logger> logger::mylog;

} /* namespace tools */

const char endline = tools::logger::endl;

template <typename type1_t, typename... types_t >
void logout(const type1_t& value, const types_t&... values) {
  tools::logger::out(value, values...);
}
