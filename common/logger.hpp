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
    using ostream_ptr = std::unique_ptr<std::ostream>;
    using currtime_func_t = std::function<std::string()>;
  public:
    ~logger_t();
    void out_to(ostream_ptr& value);
    void use_current_time(currtime_func_t value);
    template <typename type1_t, typename... types_t >
    static void out(type1_t&& value, types_t&&... values) {
      std::stringstream stream;
      if(instance()->m_curtime)
        stream << instance()->m_curtime();
      stream << value;
      out(stream, std::forward<types_t>(values)...);
    }
  public:
    static logger_ptr& instance(ostream_ptr out = logger_t::ostream_ptr());
    static std::string default_time();
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
    std::ostream* m_out;
    currtime_func_t m_curtime;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_th;
  private:
  };

} /* namespace tools */

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
