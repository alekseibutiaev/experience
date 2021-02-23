#include <ctime>
#include <map>
#include <tuple>
#include <regex>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>

//const std::string s = "210223 01:21:32.311467 130241:MSTP>D EMR.US, 2021-02-22 14:19:08.479, 86.39, /ModuleStopOrders.cpp:129";
//const std::string s = "210222 23:00:00.021091 130241:MSTP>D ARKF.US, 2021-02-22 12:08:05.043, 60.52, /ModuleStopOrders.cpp:129";
using time_point_t = std::chrono::system_clock::time_point;
using time_instr_t = std::pair<std::string, time_point_t>;
using period_t = std::tuple<time_point_t, time_point_t, std::size_t>;
enum period_member {e_from, e_to, e_count};
using periods_t = std::vector<period_t>;
using maps_t = std::map<std::string, periods_t>;

time_instr_t get_time_instr(const std::string& value) {
  static const std::regex rgx("([0-9]{6} [0-9]{2}:[0-9]{2}:[0-9]{2})\\.([0-9]+)(.* )(.+\\.[A-Z]+)(.*)");
  enum {e_full, e_time, e_microsec, e_thread, e_inst, e_tail};
  std::smatch match;
  if(std::regex_match(value, match, rgx)){
    std::tm tm = {};
    strptime(match[e_time].str().c_str(), "%y%m%d %H:%M:%S", &tm);
    time_point_t t = std::chrono::system_clock::from_time_t(std::mktime(&tm))
      /*+ std::chrono::microseconds(std::stoull(match[e_microsec].str()))*/;
    return {match[e_inst].str(), t};
  }
  return time_instr_t();
}

period_t& get_last_period(periods_t& value, const bool push) {
  if(value.empty() || push)
    value.push_back(periods_t::value_type());
  return value.back();
}

int main(int ac, char* av[]) {
  try {
    const std::string name = av[1];
    std::ifstream ifs(name);
    if(!ifs.good()) {
      std::cerr << "can`t open file. [" << name << "]" << std::endl;
      return 1;
    }
    std::size_t idx = 0;
    std::string last_inst;
    std::string line;
    maps_t maps;
    while(std::getline(ifs, line)) {
      const time_instr_t r = get_time_instr(line);
      if(last_inst.empty())
        last_inst = r.first;
      auto& tmp = maps[r.first];
      period_t& period = get_last_period(tmp, last_inst != r.first);
      if(last_inst != r.first)
        last_inst = r.first;
      if(std::get<e_from>(period) == time_point_t())
        std::get<e_from>(period) = r.second;
      else
        std::get<e_to>(period) = r.second;
      ++std::get<e_count>(period);
      if(0 == ++idx % 100000)
        std::cout << idx << std::endl;
    }
    std::cout << idx << std::endl;
    return 0;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}