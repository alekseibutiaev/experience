//*****************************************************************************
//    Project : pu40
//       File : ELogSpooler.cpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include "ELogSpooler.hpp"

#include <cstring>

namespace common {

  namespace ELogSpooler {

    const char* TypeName[] = { "CONSOLE", "SYSLOG", "FILE", "MEMORY" };

    const char* TypeName1[] = { "CONSOLE", "SYSLOG", "FILE=", "MEMORY=" };

    const char* SpoolerTypeToString( const ELogSpooler::TYPE& f_Type ){
      return ( ELogSpooler::eConsole <= f_Type ||
          ELogSpooler::eMemory >= f_Type ) ? TypeName[ f_Type ] : 0L;
    }

    ELogSpooler::TYPE StringToSpoolerType( const char* f_TypeStr,
        const char** f_ParamPtr ) {
      unsigned int len;
      if( 0 == strncasecmp( f_TypeStr, TypeName1[ ELogSpooler::eConsole ],
          strlen( TypeName1[ ELogSpooler::eConsole ] ) ) )
        return ELogSpooler::eConsole;
      else if( 0 == strncasecmp( f_TypeStr, TypeName1[ ELogSpooler::eSyslog ],
          strlen( TypeName1[ ELogSpooler::eSyslog ] ) ) )
        return ELogSpooler::eSyslog;
      else if( 0 == strncasecmp( f_TypeStr, TypeName1[ ELogSpooler::eFile ],
          ( len = strlen( TypeName1[ ELogSpooler::eFile ] ) ) ) ) {
        if( f_ParamPtr )
          *f_ParamPtr = f_TypeStr + len;
        return ELogSpooler::eFile;
      }
      else if( 0 == strncasecmp( f_TypeStr, TypeName1[ ELogSpooler::eMemory ],
          ( len = strlen( TypeName1[ ELogSpooler::eMemory ] ) ) ) ) {
        if( f_ParamPtr )
          *f_ParamPtr = f_TypeStr + len;
        return ELogSpooler::eMemory;
      }
      return ELogSpooler::eUnknown;
    }

  }; /* namespace ELogSpooler */

}; /* namespace common */

