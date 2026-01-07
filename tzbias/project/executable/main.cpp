#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#include <ctime>
#include <cerrno>
#include <cstring>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <optional>
#include <algorithm>
#include <stdexcept>

#if GCC_VERSION >= 80400
  #include <filesystem>
  using path_t = std::filesystem::path;
  using directory_iterator_t = std::filesystem::directory_iterator;
  auto is_directory = static_cast<bool(*)(const path_t&)>(std::filesystem::is_directory);
  auto is_regular_file = static_cast<bool(*)(const path_t&)>(std::filesystem::is_regular_file);
  auto is_symlink = static_cast<bool(*)(const path_t&)>(std::filesystem::is_symlink);
  auto relative = static_cast<path_t(*)(const path_t&, const path_t&)>(std::filesystem::relative);
#else
  #include <boost/filesystem.hpp>
  using path_t = boost::filesystem::path;
  using directory_iterator_t = boost::filesystem::directory_iterator;
  auto is_directory = static_cast<bool(*)(const path_t&)>(boost::filesystem::is_directory);
  auto is_regular_file = static_cast<bool(*)(const path_t&)>(boost::filesystem::is_regular_file);
  auto is_symlink = static_cast<bool(*)(const path_t&)>(boost::filesystem::is_symlink);
  auto relative = static_cast<path_t(*)(const path_t&, const path_t&)>(boost::filesystem::relative);
#endif

using tz_infos_t = std::map<std::string, long>;

class tz_control_t {
public:
  tz_control_t(const std::string& tz = std::string()) {
    if(const char* tmp = ::getenv(tz_env))
      m_cur = string_try_t(tmp);
    if(!tz.empty()) {
      if(0 != ::setenv(tz_env, tz.c_str(), true))
        throw std::runtime_error(::strerror(errno));
      ::tzset();
    }
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

void get_timezone(const std::time_t& time, tz_infos_t& infos, const std::string& tzname) {
  try {
    tz_control_t tz(tzname);
    struct tm tm;
    infos[tzname] = localtime_r(&time, &tm)->tm_gmtoff;
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void list_directory(const std::time_t& time, tz_infos_t& infos, const path_t& from, const path_t& path) {
  for(const auto& entry : directory_iterator_t(path)) {
    const path_t& tmp = entry.path();
    if(is_directory(tmp))
      list_directory(time, infos, from, tmp);
    else if(is_regular_file(tmp) && !is_symlink(tmp))
      get_timezone(time, infos, relative(tmp, from).string());
    if(is_symlink(tmp)) {
      std::cout << tmp << " " << boost::filesystem::canonical(tmp) << std::endl;
      std::cout << tmp << " " << boost::filesystem::weakly_canonical(tmp) << std::endl;
      std::cout << tmp << " " << relative(tmp, from) << std::endl;
    }
  }
}

class show_time_t {
public:
  show_time_t(const std::time_t time)
    : m_time(time) {
  }
  std::string operator()(const tz_infos_t::value_type& v) const {
    try {
      tz_control_t tz(v.first);
      std::ostringstream oss; 
      struct tm tm;
      oss << v.first << ' ' << v.second << "s " << std::setw(2) << std::setfill('0') << 
        v.second / 3600 << ':' << std::setw(2) << std::setfill('0') << v.second % 3600 / 60 <<
        std::put_time(::localtime_r(&m_time, &tm), " %a %Y-%m-%d %H:%M:%S") <<
        std::put_time(::gmtime_r(&m_time, &tm), " UTC %a %Y-%m-%d %H:%M:%S");
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

void process(const path_t& base, const std::time_t& time) {
  tz_infos_t infos;
  list_directory(time, infos, base, base);
  std::transform(infos.begin(), infos.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
    show_time_t(time));
}

int main(int ac, char* av[]) {
  try {
    std::cout << "gcc version " << GCC_VERSION << std::endl;
    const tz_control_t cur;
    const path_t tzfolder = "/usr/share/zoneinfo";
    process(tzfolder, std::time(0)); // current
    process(tzfolder, 1622548800); // 2021-06-01 12:00:00
    process(tzfolder, 1638360000); // 2021-12-01 12:00:00
    return 0;
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return -1;
}