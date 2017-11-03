// testdll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost/smart_ptr.hpp>
#include "printerdll.hpp"

int _tmain(int argc, _TCHAR* argv[]) {
  {
    std::cout << __FUNCTION__ << std::endl;
    boost::shared_ptr< test::printer > t( new test::printer() );
    t->print( "Test string.\n" );
    test::func();
  }
	return 0;
}
