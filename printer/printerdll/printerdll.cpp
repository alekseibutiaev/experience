// firsrdll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define BOOST_PRINTERDLL_SOURCE
#include <iostream>

#include "printer_impl.hpp"
#include "printerdll.hpp"

namespace test {

  printer::printer() : pv_impl( new printer_impl() ) {
    std::cout << __FUNCTION__ << std::endl;
  }

  printer::~printer(){
    std::cout << __FUNCTION__ << std::endl;
    delete pv_impl;
  }

  void printer::print( const char* f_string ){
    pv_impl->print( f_string );
  }

  void BOOST_PRINTERDLL_DECL func(){
    std::cout << __FUNCTION__ << std::endl;
  }

}; /* namespace test */
