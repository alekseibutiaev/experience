//*****************************************************************************
//    Project : pu40
//       File : ELogSpooler.hpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __ELOGSPOOLER_HPP__
#define __ELOGSPOOLER_HPP__

#include <stdio.h>

namespace common {

  namespace ELogSpooler {
    enum TYPE {
      eConsole,
      eSyslog,
      eFile,
      eMemory,
      eUnknown
    };

    const char* SpoolerTypeToString( const ELogSpooler::TYPE& f_Type );

    ELogSpooler::TYPE StringToSpoolerType( const char* f_TypeStr,
        const char** f_ParamPtr );
  }; /* namespace ELogSpooler */

}; /* namespace common */


#endif /* __ELOGSPOOLER_HPP__ */
