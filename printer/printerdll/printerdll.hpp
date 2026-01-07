#pragma once

#ifndef __PRINTERDLL_HPP__
#define __PRINTERDLL_HPP__

#include "config.hpp"

namespace test {

  class printer_impl;
  class BOOST_PRINTERDLL_DECL printer {
  public:
    printer();
    ~printer();
    void print( const char* f_string );
  private:
    printer_impl* pv_impl;
  };

  void BOOST_PRINTERDLL_DECL func();

}; /* namespace test */

#endif /* __PRINTERDLL_HPP__ */