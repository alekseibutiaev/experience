#pragma once

#ifndef __WINDLL_CPP_H__
#define __WINDLL_CPP_H__

#include <vector>
#include <list>

#include "windll_export.h"

namespace windll {

  float EXPORT_SYMBOL miltiply( const float& f_a, const float& f_b );
  double EXPORT_SYMBOL miltiply( const double& f_a, const double& f_b );
  long double EXPORT_SYMBOL miltiply( const long double& f_a, const long double& f_b );

  class EXPORT_SYMBOL int_ {
  public:
    int_( const int& f_value = 0 );
    ~int_();
  private:
    int pv_value;
  };

  class test {
  };

  class EXPORT_SYMBOL test;

}; /* namespace windll */

#endif /* __WINDLL_CPP_H__ */