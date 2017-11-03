//*****************************************************************************
//    Project : pu40
//       File : CLog.hpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CLOG_HPP__
#define __CLOG_HPP__

#include "EArgument.hpp"
#include "ELogLevel.hpp"
#include "ELogSpooler.hpp"
#include "CSinglton.hpp"
#include "CLogSpooler.hpp"
#include "CCommandLine.hpp"

#include <stdexcept>
#include <new>

namespace common {


//*****************************************************************************
// Log Level option
//*****************************************************************************
  const std::string LOGLEVEL_LONG = "log-level";
  const int LOGLEVEL_SHORT = 'L';
  const EArgument::FLAG LOGLEVEL_FLAG = EArgument::eRequiredArg;
  const std::string LOGLEVEL_DEFAULT = "WARNING";
  const std::string LOGLEVEL_DESCRIPTOR = "Set level log will by shown "
      "[ EMERG, ALERT, CRIT, ERR, WARNING, NOTICE, INFO, DEBUG ] ignoring case.";

  const COption LOGLEVEL_OPTION( LOGLEVEL_LONG, LOGLEVEL_SHORT, LOGLEVEL_FLAG,
      LOGLEVEL_DEFAULT, LOGLEVEL_DESCRIPTOR );
//*****************************************************************************
// Log Type option
//*****************************************************************************
  const std::string LOGTYPE_LONG = "log-type";
  const int LOGTYPE_SHORT = 'T';
  const EArgument::FLAG LOGTYPE_FLAG = EArgument::eRequiredArg;
  const std::string LOGTYPE_DEFAULT = "CONSOLE";
  const std::string LOGTYPE_DESCRIPTOR = "Set the log out method "
      "[ CONSOLE, SYSLOG, FILE=fileout.log, MEMORY=1024( max line ) ]"
      " ignoring case.";

  const COption LOGTYPE_OPTION( LOGTYPE_LONG, LOGTYPE_SHORT, LOGTYPE_FLAG,
      LOGTYPE_DEFAULT, LOGTYPE_DESCRIPTOR );
//*****************************************************************************

  class CLog {
  public:
    const ELogSpooler::TYPE SpoolerType() const;
    const ELogLevel::LEVEL& Level() const;
    bool Initialize( const CSinglCommandLinePtr& f_CommandLinePtr );
    void Out( const ELogLevel::LEVEL& f_Level, const char* f_ScopeName,
       const char* f_Function, const char* f_Format, ... );
  protected:
    CLog();
    ~CLog();
  private:
    Private::CLogSpoolerPtr pvLogSpooler;
    ELogLevel::LEVEL pvLevel;
  };

  typedef CSinglton< CLog > CSinglLog;
  typedef CSingltonPtr< CSinglLog > CSinglLogPtr;

  inline CSinglLogPtr Log() {
    return CSinglLog::Instance();
  }

}; /* namespace common */

#endif /* __CLOG_HPP__ */
