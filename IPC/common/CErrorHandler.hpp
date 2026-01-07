//*****************************************************************************
//    Project : pu40
//       File : CErrorHandler.hpp
// Created on : Apr 13, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CERRORHANDLER_HPP__
#define __CERRORHANDLER_HPP__

#include <cerrno>

namespace common {

  class CErrorHandler {
  public:
    int ErrorNumber() const;
    const char* ErrorString() const;
  protected:
    CErrorHandler();
    ~CErrorHandler();
  protected:
    int ptStoreErrno() const;
    void ptResetErrno( int f_Errno = 0 ) const;
  private:
    mutable int pvErrno;
  };

}; /* namespace common */

#endif /* __CERRORHANDLER_HPP__ */
