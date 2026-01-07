#include "StdAfx.h"
#include "printer_impl.hpp"

namespace test {


  printer_impl::printer_impl() : pv_value( new int( 10 ) ) {
    std::cout << __FUNCTION__ << std::endl;
  }

  printer_impl::~printer_impl(void) {
    std::cout << __FUNCTION__ << std::endl;
  }

  void printer_impl::print( const char* f_string ) {
    std::cout << *pv_value << ' ' << f_string;
  }

}; /* namespace test */
