#pragma once

#ifndef __PRINTER_IMPL_HPP__
#define __PRINTER_IMPL_HPP__

#include <boost/smart_ptr.hpp>

namespace test {

  class printer_impl {
  public:
    printer_impl();
    ~printer_impl();
    void print( const char* f_string );
  private:
    boost::shared_ptr< int > pv_value;
  };

}; /* namespace test */

#endif /* __PRINTER_IMPL_HPP__ */