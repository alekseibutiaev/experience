#pragma once

#include <ctime>
#include <cstdio>

#include <mutex>
#include <thread>
#include <memory>
#include <utility>
#include <sstream>
#include <iostream>
#include <functional>
#include <condition_variable>

#include "tools.hpp"
#include "commontypes.hpp"
#include "cache_queue.hpp"

namespace tools {

  class level_t {
  public:
    enum value_t {
      e_error,
      e_warning,
      e_info,
      e_debug
    };
  public:
    static level_t::value_t show_level;
    static const std::string str[level_t::e_debug + 1];
  };

  std::ostream& operator<<(std::ostream&, const level_t::value_t&);

  class logger_t {
  public:
    using logger_ptr = std::unique_ptr<logger_t>;
    using timeformat_t = std::function<std::string()>;
  public:
    ~logger_t();
    void out_to(ostream_ptr value = get_stdout());
    void use_time_format(timeformat_t value);
    template <typename type1_t, typename... types_t >
    static void out(type1_t&& value, types_t&&... values) {
      std::stringstream stream;
      if(instance()->m_timeformat)
        stream << instance()->m_timeformat() << ' ';
      stream << value;
      out(stream, std::forward<types_t>(values)...);
    }
  public:
    static logger_ptr& instance(ostream_ptr value = get_stdout());
    static ostream_ptr get_stdout();
  private:
    typedef cache_queue<std::string> storage_t;
  private:
    logger_t(ostream_ptr& out);
    void stop();
    void out_int(const std::string& value);
    void out_tread();
    static void out(std::stringstream& stream);
    template <typename type1_t, typename... types_t >
    static void out(std::stringstream& stream, type1_t&& value, types_t&&... values) {
      stream << value;
      out(stream, std::forward<types_t>(values)...);
    }
  private:
    bool m_stop;
    ostream_ptr m_stream;
    timeformat_t m_timeformat;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_th;
  private:
  };

  struct function_name_t {
    function_name_t(const char* f, const int i) : m_f(f), m_i(i){}
    const char* m_f;
    int m_i;
  };

  std::ostream& operator<<(std::ostream& os, const function_name_t& v);

} /* namespace tools */

//#define _FN_ tools::function_name_t(__PRETTY_FUNCTION__, __LINE__)
#define _FN_ tools::function_name_t(__FUNCTION__, __LINE__)

extern const char* endline;

template <typename type1_t, typename... types_t>
void lo(type1_t&& value, types_t&&... values) {
  tools::logger_t::out(std::forward<type1_t>(value), std::forward<types_t>(values)...);
}

template <typename... types_t>
void lo(const tools::level_t::value_t value, types_t&&... values) {
  if(tools::level_t::show_level >= value)
    tools::logger_t::out(value, std::forward<types_t>(values)...);
}

template <typename... types_t>
void _debug(types_t&&... values) {
  if(tools::level_t::show_level >= tools::level_t::e_debug)
    tools::logger_t::out(tools::level_t::e_debug, std::forward<types_t>(values)...);
}

template <typename... types_t>
void _info(types_t&&... values) {
  if(tools::level_t::show_level >= tools::level_t::e_info)
    tools::logger_t::out(tools::level_t::e_info, std::forward<types_t>(values)...);
}

template <typename... types_t>
void _warning(types_t&&... values) {
  if(tools::level_t::show_level >= tools::level_t::e_warning)
    tools::logger_t::out(tools::level_t::e_warning, std::forward<types_t>(values)...);
}

template <typename... types_t>
void _error(types_t&&... values) {
  if(tools::level_t::show_level >= tools::level_t::e_error)
    tools::logger_t::out(tools::level_t::e_error, std::forward<types_t>(values)...);
}

using lv_t = tools::level_t;
