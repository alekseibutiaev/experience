#include <cstdio>

#include "timeformat.hpp"
#include "logger.hpp"

namespace tools {

  level_t::value_t level_t::show_level = level_t::e_info;

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

  logger_t::logger_t(ostream_ptr& value)
      : m_stop(false)
      , m_stream(std::move(value))
      , m_timeformat(std::bind(&tools::time_milliseconds, 0))
      , m_th([&](){out_tread();}) {
  }

  logger_t::~logger_t() {
    stop();
  }

  void logger_t::out_to(ostream_ptr value) {
    m_stream = std::move(value);
  }

  void logger_t::use_time_format(timeformat_t value) {
    std::unique_lock<std::mutex> _(m_mtx);
    m_timeformat = value;
  }

  logger_t::logger_ptr& logger_t::instance(ostream_ptr value) {
    static logger_ptr mylog;
    if(!mylog)
      mylog.reset(new logger_t(value));
    return mylog;
  }

  ostream_ptr logger_t::get_stdout() {
    return ostream_ptr(&std::cout, [](ostream_ptr::element_type*){});
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
        ostream_ptr os = m_stream;
        std::copy(local.begin(), local.end(), std::ostream_iterator<std::string>(*os));
        os->flush();
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
