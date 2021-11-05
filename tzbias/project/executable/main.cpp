#include <errno.h>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <map>
#include <string>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <optional>
#include <algorithm>
#include <stdexcept>
#include <experimental/filesystem>

using tz_infos_t = std::map<std::string, long>;
using tz_info_t = tz_infos_t::value_type;
using path_t = std::experimental::filesystem::path;

class tz_control_t {
public:
  tz_control_t(const std::string& tz = std::string()) {
    const char* tmp = ::getenv(tz_env);
    m_cur = tmp ? string_try_t(tmp) : string_try_t();
    if(!tz.empty() && 0 != ::setenv(tz_env, tz.c_str(), true)) {
      char buf[256];
      throw std::runtime_error(::strerror_r(errno, buf, sizeof buf));
    }
    ::tzset();
  }
  ~tz_control_t() {
    m_cur ? ::setenv(tz_env, m_cur->c_str(), true) : ::unsetenv(tz_env);
  }
private:
  using string_try_t = std::optional<std::string>;
private:
  string_try_t m_cur;
private:
  static const char* tz_env;
};

const char* tz_control_t::tz_env = "TZ";

void get_timezone(const std::time_t& time, tz_infos_t& infos, const path_t& from, const path_t& path) {
  try {
    const auto tzname = std::accumulate(std::mismatch(from.begin(), from.end(), path.begin()).second,
      path.end(), path_t(), [](path_t& a, const path_t& b){ return a /= b; }).string();
    tz_control_t tz(tzname);
    struct tm lctm;
    infos[tzname] = localtime_r(&time, &lctm)->tm_gmtoff;
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void list_directory(const std::time_t& time, tz_infos_t& infos, const path_t& from, const path_t& path) {
  for(const auto& entry : std::experimental::filesystem::directory_iterator(path))
    if(std::experimental::filesystem::is_directory(entry))
      list_directory(time, infos, from, entry.path());
    else if(std::experimental::filesystem::is_regular_file(entry))
      get_timezone(time, infos, from, entry.path());
}

class show_time_t {
public:
  show_time_t(const std::time_t time)
    : m_time(time) {
  }
  std::string operator()(const tz_info_t& v) const {
    try {
      tz_control_t tz(v.first);
      char buf[256];
      struct tm tm;
      const auto pos = strftime(buf, sizeof buf, " %a %Y-%m-%d %H:%M:%S", ::localtime_r(&m_time, &tm));
      strftime(buf + pos, sizeof buf - pos, " UTC %a %Y-%m-%d %H:%M:%S", gmtime_r(&m_time, &tm));
      std::ostringstream oss;
      oss << v.first << ' ' << v.second << "s " << std::setw(2) << std::setfill('0') << 
        v.second / 3600 << ':' << std::setw(2) << std::setfill('0') << v.second % 3600 / 60 << buf;
      return oss.str();
    }
    catch(const std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    return v.first + " " + std::to_string(v.second);
  }
private:
  const std::time_t m_time;
};

int main(int ac, char* av[]) {
  try {
    const tz_control_t cur();
    const std::experimental::filesystem::path tzfolder = "/usr/share/zoneinfo";
    tz_infos_t infos;
    const auto& time = ::time(0);
    list_directory(time, infos, tzfolder, tzfolder);
  //  list_directory(1622877451, infos, tzfolder, tzfolder);
    std::transform(infos.begin(), infos.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
      show_time_t(time));
    return 0;
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return -1;
}