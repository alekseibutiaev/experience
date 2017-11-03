//*****************************************************************************
//    Project : pu40
//       File : showdata.cpp
// Created on : May 27, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#include <cstdio>
#include <sstream>

#include "CLog.hpp"

#include "showdata.hpp"

namespace common {

  const unsigned int BUF_SIZE = 20;

  void showdata( const char* f_Scope, const char* f_Function,
      const void* f_Data, const unsigned short& f_Size ) {
    const unsigned char* data = reinterpret_cast< const unsigned char* >( f_Data );
    std::ostringstream os;
    os << std::endl;
    os << "-------+--0----1----2----3----4----5----6----7----8----9--"
        "--A----B----C----В----E----F--";
    char buf[ BUF_SIZE + 1 ];
    for( unsigned short i = 0; i < f_Size; ++i ) {
      if( i % 16 )
        buf[ snprintf( buf, BUF_SIZE, " 0x%02X", data[ i ] ) ] = '\0';
      else {
        buf[ snprintf( buf, BUF_SIZE, "\n0x%04X ! 0x%02X", i, data[ i ] ) ] = '\0';
      }
      os << buf;
    }
    os << std::endl << "-------+---------------------------------------------"
        "-----------------------------------";
    common::Log()->Out( common::ELogLevel::eAlways, f_Scope, f_Function,
        "Show buffer.%s\n", os.str().c_str() );
/*
    printf( "0x%02X%c", f_Data[ i ] & 0xff, ( i + 1 ) % 16 ? ' ' : '\n' );
    printf( "\n" );
*/
  }

}; /* namespace common */
