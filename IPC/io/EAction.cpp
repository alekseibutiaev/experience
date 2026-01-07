//*****************************************************************************
//    Project : pu40
//       File : EAction.cpp
// Created on : Dec 12, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#include <poll.h>

#include "EAction.hpp"

namespace io {

  unsigned short POSIX_VALUE[] = { POLLIN, POLLOUT, POLLPRI, POLLERR,
    POLLHUP, POLLNVAL };

  const unsigned short& ToPosix( const EAction::TYPE& f_Action ) {
    return POSIX_VALUE[ f_Action ];
  }

}; /* namespace io */
