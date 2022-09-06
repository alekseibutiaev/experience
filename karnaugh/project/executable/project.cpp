#include <cstdio>
#include <iostream>

#include <library/karnaugh.h>

int main(int ac, char* av[]) {
  std::cout << "project" << std::endl;
  kh::print(17);
  kh::khmap_t thmap(5);
  thmap.set(0, 1);
  thmap.set(31, 1);
  return 0;
}