//*****************************************************************************
//    Project : pu40
//       File : CLog.cpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include <cassert>
#include <cstdarg>
#include <cstdio>

#include "CLog.hpp"
#include "ELogLevel.hpp"
#include "CMemorySpooler.hpp"

namespace common {

  const char* const TIME_FORMAT = "%Y-%m-%d/%X";
  const char* const LOG_FORMAT = "%-7s: %s %s::%s: %s";
  const char* const DEEP_MEMORY_SPOLLER = "512";

//*****************************************************************************
  CLog::CLog() : pvLevel( ELogLevel::eDebug ) {
      pvLogSpooler = Private::CLogSpoolerPtr(
      Private::CLogSpooler::Create( ELogSpooler::eMemory,
      DEEP_MEMORY_SPOLLER ) );
  }
//*****************************************************************************
  CLog::~CLog() {
  }
//*****************************************************************************
  const ELogSpooler::TYPE CLog::SpoolerType() const {
    return pvLogSpooler->Type();
  }
//*****************************************************************************
  const ELogLevel::LEVEL& CLog::Level() const {
    return pvLevel;
  }
//*****************************************************************************
  bool CLog::Initialize( const CSinglCommandLinePtr& f_CommandLinePtr ) {
    std::string value;
    ELogLevel::LEVEL level;
    ELogSpooler::TYPE type;
    // get log level option
    const COption* opt = f_CommandLinePtr->Option( LOGLEVEL_SHORT );
    opt->GetValue( value );
    // check up argument of the log level
    if( ELogLevel::eUnknown ==
        ( level = ELogLevel::StringToLevel( value.c_str() ) ) ) {
      BadParameter( value.c_str(), opt->ShortOption(), opt->LongOption().c_str() );
      f_CommandLinePtr->ShowHelp();
      return false;
    }
    pvLevel = level;
    // get log spooler type option
    const char* optionParam = 0L;
    opt = f_CommandLinePtr->Option( LOGTYPE_SHORT );
    opt->GetValue( value );
    // check up argument of the log type
    if( ELogSpooler::eUnknown == ( type =
          ELogSpooler::StringToSpoolerType( value.c_str(), &optionParam ) ) ) {
      BadParameter( value.c_str(), opt->ShortOption(), opt->LongOption().c_str() );
      f_CommandLinePtr->ShowHelp();
      return false;
    }
    // create new spooler
    try {
      // create new spooler
      Private::CLogSpooler* newSpooler =
          Private::CLogSpooler::Create( type, optionParam );
      // check up current spooler
      if( Private::CMemorySpooler* oldSpooler =
          dynamic_cast< Private::CMemorySpooler* >( pvLogSpooler.get() ) )
        // move logs from memory in to new log
        oldSpooler->MoveTo( *newSpooler );
      // set new spooler of log
      pvLogSpooler = Private::CLogSpoolerPtr( newSpooler );
      return true;
    }
    catch ( std::bad_alloc ){
      fputs( "Object of the a spool has not been created.\n", stderr );
      return false;
    }
  }
//*****************************************************************************
  void CLog::Out( const ELogLevel::LEVEL& f_Level, const char* f_ScopeName,
      const char* f_Function, const char* f_Format, ... ){
#define BUF_MAX 768
#define TIME_BUF_MAX 64
    //  check up log level
    assert( pvLevel <= ELogLevel::eDebug );
    if( f_Level <= pvLevel ){
      va_list list;
      va_start( list, f_Format );
      time_t tm = time( 0 );
      char timebuf[ TIME_BUF_MAX ];
      timebuf[ strftime( timebuf, TIME_BUF_MAX - 1, TIME_FORMAT,
          localtime( &tm ) ) ] = '\0';
      char buf[ BUF_MAX ];
      buf[ snprintf( buf, BUF_MAX - 1, LOG_FORMAT, LevelToString( f_Level ),
          timebuf, f_ScopeName, f_Function, f_Format ) ] = '\0';
      pvLogSpooler->Out( f_Level, buf , list );
      va_end( list );
    }
#undef BUF_MAX
#undef TIME_BUF_MAX
  }

}
