#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <pugixml.hpp>

void foo(const pugi::xml_node& f) {
  if(f)
    f.print(std::cout);
  else
    std::cout << "empty" << std::endl;
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
      const pugi::xml_node node = doc.first_child();
      foo(node);
      const pugi::xml_node node1 = node.child("cfg1");
      foo(node1);
      const pugi::xml_node node2 = node1.select_node("module[@type=\"QSRV\"]").node();
      foo(node2);
    }
    else
      throw(std::runtime_error(res.description()));
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return EXIT_SUCCESS;
}