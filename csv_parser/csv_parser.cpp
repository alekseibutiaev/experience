#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

int main(int ac, char* av[]){
  if(ac < 2)
    return -1;
  std::vector<std::vector<std::string>> data;
  std::cout << "prepare " << av[1] << std::endl;
  std::ifstream file(av[1]);
  if(!file.good()) {
    std::cout << "file: " << av[1] << "is wrong" << std::endl;
    return -1;
  }
    
  while(!file.eof()){
    std::string line;
    getline(file, line);
    std::stringstream ss(line);
    std::vector<std::string> data_line;
    std::copy(std::istream_iterator<std::string>(ss),
      std::istream_iterator<std::string>(), std::back_inserter(data_line));
    data.emplace_back(data_line);
  }
  for(const auto& i : data) {
    std::copy(i.begin(), i.end(), std::ostream_iterator<std::string>(std::cout,", "));
    std::cout << std::endl;
  }
  return 0;
}
