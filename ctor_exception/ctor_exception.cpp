// ctor_exception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdexcept>
#include <iostream>

class first {
public:
  first() {
    std::cout << __FUNCTION__ << std::endl;
  }
  ~first(){
    std::cout << __FUNCTION__ << std::endl;
  }
};

class second {
public:
  second() {
    std::cout << __FUNCTION__ << std::endl;
    throw( std::runtime_error( "hello" ) );
  }
  ~second() {
    std::cout << __FUNCTION__ << std::endl;
  }
private:
  first pv_f;
};

int _tmain(int argc, _TCHAR* argv[])
{
  try {
    second s;
  }
  catch( const std::exception& e ) {
    std::cerr << e.what() << std::endl;
  }
	return 0;
}

