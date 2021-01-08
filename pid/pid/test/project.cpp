#include <iostream>

#include <libpid/libpid.h>

int main(int ac, char* av[]) {
  pid::pid_t pid = pid::pid_t(0.1, 100, -100, 0.1, 0.01, 1.5);
  double val = 70;
  for (int i = 0; i < 1000; i++) {
      double inc = pid.calculate(0, val);
      std::cout << i << " val: " << val << " inc: " << inc << std::endl;
      val += inc;
  }
  return 0;
}