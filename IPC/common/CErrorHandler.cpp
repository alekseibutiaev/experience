//*****************************************************************************
//    Project : pu40
//       File : CErrorHandler.cpp
// Created on : Apr 13, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#include <string.h>

#include "CErrorHandler.hpp"

namespace common {

//*****************************************************************************
  CErrorHandler::CErrorHandler() : pvErrno( 0 ) {
  }
//*****************************************************************************
  CErrorHandler::~CErrorHandler() {
  }
//*****************************************************************************
  int CErrorHandler::ErrorNumber() const {
    return pvErrno;
  }
//*****************************************************************************
  const char* CErrorHandler::ErrorString() const {
    return strerror( pvErrno );
  }
//*****************************************************************************
  int CErrorHandler::ptStoreErrno() const {
    return pvErrno = errno;
  }
//*****************************************************************************
  void CErrorHandler::ptResetErrno( int f_Errno ) const {
    pvErrno = f_Errno;
  }

} /* namespace common */
