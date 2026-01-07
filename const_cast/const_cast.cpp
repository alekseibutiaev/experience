//============================================================================
// Name        : const_cast.cpp
// Author      : Butyaev Alexey
// Version     :
// Copyright   : alexsyrezerv@mail.ru
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

int main( int ac, char* av[] ) {
  try {
    const int i = 7000;
    int* j = const_cast<int*>(&i);
    std::cout << "&i : " << &i << " j : " << j << std::endl;  // adresses are same
    std::cout << "*j : " << *j << std::endl;
    *j = 9000;                                                // NOTE: may cause error depending on the compiler
    std::cout << "&i : " << &i << " j : " << j << std::endl;  // adresses are same
    std::cout << "*j : " << *j << std::endl;                  // 9000 in clang++
    std::cout << "i : " << i << std::endl;                    // 7000 in clang++

    // int x = 10;
    // int* y = &x;
    // *y = 11;
    // cout << "&x : " << &x << " y : " << y << endl; // adresses are same
    // cout << "x : " << x << endl;
    // cout << "*y : " << *y << endl;
  }
  catch( std::exception& e ) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
