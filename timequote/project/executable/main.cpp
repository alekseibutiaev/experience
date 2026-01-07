#include <ctime>
#include <map>
#include <tuple>
#include <regex>
#include <limits>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>

using seconds_t = std::chrono::seconds;
using time_point_t = std::chrono::system_clock::time_point;
using time_instr_t = std::pair<std::string, time_point_t>;
using period_t = std::tuple<time_point_t, time_point_t, std::size_t>;
enum period_member {e_from, e_to, e_count};
using periods_t = std::vector<period_t>;
using maps_t = std::map<std::string, periods_t>;

const std::string s0 = "210222 16:02:41.555696 15866:MSTP>D EBFNDT, 2021-02-22 16:02:41.454, 53625.36, /ModuleStopOrders.cpp:127";
const std::string s1 = "210222 16:02:41.555696 15866:MSTP>D EBFNDT.US, 2021-02-22 16:02:41.454, 53625.36, /ModuleStopOrders.cpp:127";
const std::string s2 = "210222 16:02:41.555696 15866:MSTP>D DFR+.US, 2021-02-22 16:02:41.454, 53625.36, /ModuleStopOrders.cpp:127";
const std::string s3 = "210222 16:02:41.555696 15866:MSTP>D 0R+.US, 2021-02-22 16:02:41.454, 53625.36, /ModuleStopOrders.cpp:127";

time_instr_t get_time_instr(const std::string& value) {
  static const char* time_format = "%y%m%d %H:%M:%S";
//  static const std::regex rgx("([0-9]{6} [0-9]{2}:[0-9]{2}:[0-9]{2})\\.([0-9]+)(.* )(.+\\.[A-Z]+)(.*)");
  static const std::regex rgx("([0-9]{6} [0-9]{2}:[0-9]{2}:[0-9]{2})\\.([0-9]+)(.* )([0-9A-Z\\-\\+\\_]+\\.?[A-Z]+)(.*)");
  enum {e_full, e_time, e_microsec, e_thread, e_inst, e_tail};
  std::smatch match;
  if(std::regex_match(value, match, rgx)) {
    std::tm tm = {};
    strptime(match[e_time].str().c_str(), time_format, &tm);
    return {match[e_inst].str(), std::chrono::system_clock::from_time_t(std::mktime(&tm))};
  }
  return time_instr_t();
}

period_t& get_period(periods_t& value, const time_point_t tp) {
  bool add = false;
  bool e = value.empty();
//  while(value.empty() || seconds_t(1) < std::chrono::duration_cast<seconds_t>(tp - std::get<e_to>(value.back())))
  while(e || (add = seconds_t(0) < std::chrono::duration_cast<seconds_t>(tp - std::get<e_to>(value.back())))) {
    value.push_back(periods_t::value_type());
    break;
  }
  return value.back();
}

void fill_empty(std::ostream& os, time_point_t from, const time_point_t& to, const std::string& value = "0") {
  for(;from <= to; from = from + seconds_t(1))
    os << value << ';';
}

int main(int ac, char* av[]) {
  try {
/*
    auto ff0 = get_time_instr(s0);
    auto ff1 = get_time_instr(s1);
    auto ff2 = get_time_instr(s2);
    auto ff3 = get_time_instr(s3);
*/
    time_point_t min_time = std::chrono::system_clock::now();
    time_point_t max_time = time_point_t();
    const std::string name = av[1];
    std::ifstream ifs(name);
    if(!ifs.good()) {
      std::cerr << "can`t open file. [" << name << "]" << std::endl;
      return 1;
    }
    std::size_t idx = 0;
    std::string line;
    maps_t maps;
    while(std::getline(ifs, line)) {
      const time_instr_t quote = get_time_instr(line);
      if(quote.first.empty())
        std::cout << line << std::endl;
      min_time = std::min<time_point_t>(min_time, quote.second);
      max_time = std::max<time_point_t>(max_time, quote.second);
      auto& tmp = maps[quote.first];
      period_t& period = get_period(tmp, quote.second);
      if(std::get<e_from>(period) == time_point_t())
        std::get<e_from>(period) = quote.second;
      std::get<e_to>(period) = quote.second;
      ++std::get<e_count>(period);
      if(0 == ++idx % 1000000)
        std::cout << idx << std::endl;
    }
    std::cout << "period: " << std::chrono::duration_cast<seconds_t>(max_time - min_time).count() << " sec." << std::endl;
    const std::string out = av[2];
    std::ofstream ofs(av[2]);
    for(const auto& inst : maps) {
      ofs << inst.first << ';';
      time_point_t priv = min_time;
      for(const period_t& period : inst.second) {
        fill_empty(ofs, priv, std::get<e_from>(period));
        priv = std::get<e_to>(period);
        const std::size_t semp =  std::get<e_count>(period) /
          (std::chrono::duration_cast<seconds_t>(priv - std::get<e_from>(period)).count() + 1);
        fill_empty(ofs, std::get<e_from>(period), priv, std::to_string(semp));
      }
      fill_empty(ofs, priv, max_time);
      ofs << std::endl;
    }
    return 0;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}