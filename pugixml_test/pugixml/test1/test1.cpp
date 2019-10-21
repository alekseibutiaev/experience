#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <pugixml.hpp>

template<typename type_t>
void foo(const type_t& f) {

}

int main(int ac, char* av[]) {
  std::cout << av[1] << std::endl;
  std::ifstream ifs(av[1]);
  if(!ifs)
    return EXIT_FAILURE;
  //"module[@type=\"QSRV\"]"
  try {
    pugi::xml_document doc;
    if(const auto& res = doc.load(ifs)) {
      const pugi::xml_node& node = doc.first_child();
      const auto& ppp = node.select_node("module[@type=\"QSRV\"]");
      foo(ppp);
    }
    else
      throw(std::runtime_error(res.description()));
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return EXIT_SUCCESS;
}