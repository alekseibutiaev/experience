//*****************************************************************************
//    Project : pu40
//       File : CVaList.hpp
// Created on : Apr 13, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CVALIST_HPP__
#define __CVALIST_HPP__

#include <cstdarg>

namespace common {

  class CVaList {
  public:
    CVaList();
    ~CVaList();
    va_list& GetList();
    template< typename GETTYPE >
    GETTYPE NextArg( const GETTYPE& ) {
      return va_arg( pvList, GETTYPE );
    }
  private:
    va_list pvList;
  };

}; /* namespace common */

#endif /* __CVALIST_HPP__ */
