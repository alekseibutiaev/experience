//#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <iostream>
#include <map>
#include <experimental/filesystem>

//const std::filesystem::path tzfolder{"/usr/share/zoneinfo"};

const char* tz_env = "TZ";
using tz_infos_t = std::map<std::string, long>;
using tz_info_t = tz_infos_t::value_type;

std::string get_tz() {
  const char* tz = ::getenv(tz_env);
  return 0 == tz ? std::string() : tz;
}

void set_tz(const std::string& tz) {
  ::setenv(tz_env, tz.c_str(), true);
}

void get_timezone(const std::time_t& time, tz_infos_t& infos, const std::experimental::filesystem::path& path) {
  char buf[300];
  struct tm lctm;
  struct tm gmtm;
  const auto& str = path.string();
  set_tz(str);
  ::tzset();
  localtime_r(&time, &lctm);

  const auto& o = infos[str] = lctm.tm_gmtoff;
  auto pos = strftime(buf, sizeof buf, " %a %Y-%m-%d %H:%M:%S %Z %z", &lctm);
  buf[pos++] = ' ';
  strftime(buf + pos, sizeof buf - pos, " %a %Y-%m-%d %H:%M:%S %Z %z",  gmtime_r(&time, &gmtm));
  std::cout << str << " " << o << " " << tzname[0] << " " << tzname[1] << buf << std::endl;
  if(std::string::npos != str.find("New York") || std::string::npos != str.find("Moscow"))
    std::cout << "";
}

void list_directory(const std::time_t& time, tz_infos_t& infos, const std::experimental::filesystem::path& folder) {
  for(const auto& entry : std::experimental::filesystem::directory_iterator(folder))
    if(std::experimental::filesystem::is_directory(entry))
      list_directory(time, infos, entry.path().c_str());
    else if(std::experimental::filesystem::is_regular_file(entry))
      get_timezone(time, infos, entry.path());
}

int main(int ac, char* av[]) {
  const std::string curtz = get_tz();
  const std::experimental::filesystem::path tzfolder = "/usr/share/zoneinfo";
  const time_t cur = ::time(0);
  tz_infos_t infos;
  list_directory(cur, infos, tzfolder);
  return 0;
}