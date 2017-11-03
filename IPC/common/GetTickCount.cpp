//*****************************************************************************
//    Project : pu40
//       File : GetTickCount.cpp
// Created on : Apr 25, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#include <sys/time.h>

#include "GetTickCount.hpp"

namespace common {

  const unsigned long long TICKSPERSEC = 10000000;
  const unsigned long long SECSPERDAY = 86400;
  const unsigned long long SECS_1970_TO_2010 =
      ( ( 40 * 365 + 10 ) * SECSPERDAY );
  const unsigned long long TICKS_1970_TO_2010 =
      ( SECS_1970_TO_2010 * TICKSPERSEC );
  const unsigned long long DELEMITER = 10000;

  unsigned long long GetTickCount() {
    struct timeval now;
    gettimeofday( &now, 0 );
    unsigned long long tmp = ( now.tv_sec * TICKSPERSEC -
        TICKS_1970_TO_2010 + now.tv_usec * 10 ) / DELEMITER;
    return tmp;
  }

}
