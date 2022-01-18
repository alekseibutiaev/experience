#include <string>
#include <iostream>

void bp_bool(bool v) {
  std::cout << v << std::endl;
  return;
}

void bp_int(int v) {
  std::cout << v << std::endl;
  return;
}

void bp_string(const std::string& v) {
  std::cout << v << std::endl;
  return;
}

int main(int ac, char* av[]) {
  bp_bool(false);
  bp_bool(true);
  bp_int(0);
  bp_int(10);
  bp_string("string");
  bp_string("test");
  return 0;
}

