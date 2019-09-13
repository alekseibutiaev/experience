#include <cstdio>
#include <chrono>
#include <iterator>

#include "logger.hpp"

namespace tools {

  level_t::value_t level_t::show_level = level_t::e_debug;

  const std::string level_t::str[level_t::e_debug + 1] = {
    "ERROR   ",
    "WARNING ",
    "INFO    ",
    "DEBUG   "
  };

  std::ostream& operator<<(std::ostream& os, const level_t::value_t& value) {
    os << level_t::str[value];
    return os;
  }

  logger_t::logger_t(ostream_ptr& out)
      : m_stop(false)
      , m_stream(std::move(out))
      , m_out(m_stream ? m_stream.get() : &std::cout)
      , m_th([&]() {out_tread();}) {
  }

  logger_t::~logger_t() {
    stop();
  }

  void logger_t::out_to(ostream_ptr& value) {
    std::unique_lock<std::mutex> _(m_mtx);
    m_stream = std::move(value);
    m_out = m_stream ? m_stream.get() : &std::cout;
  }

  void logger_t::use_current_time(currtime_func_t value) {
    std::unique_lock<std::mutex> _(m_mtx);
    m_curtime = value;
  }

  logger_t::logger_ptr& logger_t::instance(logger_t::ostream_ptr out) {
    static logger_ptr mylog;
    if(!mylog)
      mylog.reset(new logger_t(out));
    return mylog;
  }

  std::string logger_t::default_time() {
    char buf[64];
    const auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    const auto sec = now / 1000;
    const std::size_t pos = strftime(buf, std::size(buf), "%F %T", std::localtime(&sec));
    snprintf(buf + pos, std::size(buf) - pos, ".%03ld ", now % 1000);
    return std::string(buf);
  }

  void logger_t::stop() {
    if(m_th.joinable()) {
      {
        std::unique_lock<std::mutex> _(m_mtx);
        m_stop = true;
        m_cv.notify_one();
      }
      m_th.join();
    }
  }

  void logger_t::out_int(const std::string& value) {
    std::unique_lock<std::mutex> _(m_mtx);
    m_queue.add(value);
    m_cv.notify_one();
  }

  void logger_t::out_tread() {
    try {
      storage_t::queue_t local;
      while(!m_stop || !m_queue.empty()) {
        {
          std::unique_lock<std::mutex> _(m_mtx);
          while(!m_stop && m_queue.empty())
            m_cv.wait(_);
          local.swap(m_queue.data());
        }
        std::copy(local.begin(), local.end(), std::ostream_iterator<std::string>(*m_out));
        m_out->flush();
        std::unique_lock<std::mutex> _(m_mtx);
        m_queue.store_data(local);
      }
    }
    catch(const std::exception& e) {
      std::cerr << e.what()<< std::endl;
    }
  }

  void logger_t::out(std::stringstream& stream) {
    if(instance())
      instance()->out_int(stream.str());
    else
      std::puts(stream.str().c_str());
  }

  std::ostream& operator<<(std::ostream& os, const function_name_t& v) {
    if(level_t::show_level == level_t::e_debug)
      os << v.m_f << ':' << v.m_i << ' ';
    return os;
  }

} /* namespace tools */

const char* endline = "\n";
