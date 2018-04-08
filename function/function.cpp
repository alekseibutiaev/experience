#include <iostream>
#include <functional>

void multiple(int lvalue, int rvalue) {
  std::cout << lvalue << '*' << rvalue << '=' << lvalue * rvalue << std::endl;
}

void mult(std::function<void(int)> f) {
  for(int i = 0; i < 10; ++i)
    f(i);
}

int main(int, char**) {

  multiple(5,5);

  mult(std::bind(multiple, 5, std::placeholders::_1));


  return 0;
}
