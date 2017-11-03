//*****************************************************************************
//    Project : pu40
//       File : ELogLevel.hpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __ELOGLEVEL_HPP__
#define __ELOGLEVEL_HPP__

namespace common {

  namespace ELogLevel {
    enum LEVEL {
      eAlways   = 0,
      eEmerg,         // system is unusable
      eAlert,         // action must be taken immediately
      eCrit,          // critical conditions
      eErr,           // error conditions
      eWarning,       // warning conditions
      eNotice,        // normal, but significant, condition
      eInfo,          // informational message
      eDebug,         // debug-level message
      eUnknown
    };

    const char* LevelToString( const ELogLevel::LEVEL& f_Level );
    ELogLevel::LEVEL StringToLevel( const char* f_LevelStr );
  }; /* namespace ELogLevel */

}; /* namespace common */

#endif /* __ELOGLEVEL_HPP__ */
