#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using strings_t = std::vector<std::string>;
using sarray_t = std::vector<strings_t>;

int main(int ac, char* av[]) {
  sarray_t array;
  std::ifstream ifs(av[2]);
  sarray_t::iterator ait;
  if(ifs.good()) {
    std::string s;
    while(std::getline(ifs, s)) {
      strings_t::const_iterator pit;
      if(!array.empty()) {
        ait = array.end() - 1;
        pit = ait->begin();
      }
      array.emplace_back();
      strings_t& strs = array.back();
      for(std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
        if(*it == '*')
          strs.emplace_back(*pit++);
        else {
          strs.emplace_back(std::string(it, s.cend()));
          break;
        }
      }
    }
  }
  const std::string ns = av[1];
  std::for_each(array.begin(), array.end(), [&ns](const strings_t& v){
    if(v.size() <= 1)
      return;
    std::string s = ns;
    for(const auto& i : v)
      s = s + "::" + i;
    std::cout << "    {\"" << s << "\", &create_group<" << s << ">}," << std::endl;
  });
  std::cout << array.size() << std::endl;
  return 0;
}
