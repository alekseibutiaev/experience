#include <iostream>
#include <stdexcept>

void function0() {
  throw(std::runtime_error(__FUNCTION__));
}

void function1() {
  throw(std::logic_error(__FUNCTION__));
}


int main(int ac, char* av[]) {
  std::cout << "project" << std::endl;
  try {
    function0();
  }
  catch(const std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
  try {
    function1();
  }
  catch(const std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
  return 0;
}
