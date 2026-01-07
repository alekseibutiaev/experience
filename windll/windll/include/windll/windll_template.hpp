#pragma once

#ifndef __WINDLL_TEMPLATE_H__
#define __WINDLL_TEMPLATE_H__

#include <set>
#include <deque>
#include <map>
#include <list>
#include <vector>

#include "windll_export.h"
#include "windll_stl_export.hpp"

namespace windll {

  EXPORT_STL_VECTOR( EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, double );

  EXPORT_STL_VECTOR( EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, int );

  EXPORT_STL_LIST( EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, unsigned short );

  EXPORT_STL_SET( EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, int );

  EXPORT_STL_MULTISET( EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, long );

  EXPORT_STL_MAP( EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, unsigned short, unsigned long );

  EXPORT_STL_MULTIMAP( EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, long double, long long );

  EXPORT_STL_DEQUE(  EXTERN_IMPLEMENTATION_TEMPLATE, EXPORT_SYMBOL, float );

  class EXPORT_SYMBOL keepvector {
  public:
    std::vector< double >::iterator begin();
  private:
    std::vector< double > pv_array;
  };

  class EXPORT_SYMBOL test2 : std::vector< int > {
  public:
    using std::vector< int >::begin;
  };

}; /* namespace windll */

#endif /* __WINDLL_TEMPLATE_H__ */
