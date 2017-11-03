#include "stdafx.h"

#include <string>

#include <windll/windll_cpp.hpp>

namespace windll {

  float miltiply( const float& f_a, const float& f_b ) {
    return f_a * f_b;
  }

  double miltiply( const double& f_a, const double& f_b ) {
    return f_a * f_b;
  }

  long double miltiply( const long double& f_a, const long double& f_b ) {
    return f_a * f_b;
  }

  int_::int_( const int& f_value ): pv_value( f_value ) {
  }

  int_::~int_() {
  }
#if 0
  std::list< double > int_array::pv_list;

  int_array::int_array( const int& f_size ) : pv_array( f_size ) {
  }

  int_array::~int_array(){
  }

  int& int_array::operator[]( const int& f_index ) {
    return pv_array[ f_index ];
  }

  const int& int_array::operator[]( const int& f_index ) const {
    return pv_array[ f_index ];
  }
#endif
}; /* namespace windll */
