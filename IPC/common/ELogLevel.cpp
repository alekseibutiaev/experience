//*****************************************************************************
//    Project : pu40
//       File : ELogLevel.cpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include "ELogLevel.hpp"
#include <cstring>

namespace common {

  namespace ELogLevel {

    const char* LevelName[] = { "ALWAYS", "EMERG", "ALETR", "CRIT", "ERR",
       "WARNING", "NOTICE", "INFO", "DEBUG" };

    const char* LevelToString( const ELogLevel::LEVEL& f_Level ) {
      return ( ELogLevel::eEmerg <= f_Level || ELogLevel::eDebug >= f_Level ) ?
          LevelName[ f_Level ] : 0L;
    }

    ELogLevel::LEVEL StringToLevel( const char* f_LevelStr ) {
      int level = ELogLevel::eEmerg;
      while( level < ELogLevel::eUnknown &&
          0 != strcasecmp( LevelName[ level ], f_LevelStr ) )
        ++level;
      return static_cast< ELogLevel::LEVEL >( level );
    }

  }; /* namespace ELogLevel */

}; /* namespace common */
