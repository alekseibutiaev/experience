//*****************************************************************************
//    Project : pu40
//       File : CSyslogSpooler.cpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include "CSyslogSpooler.hpp"
#include "CCommandLine.hpp"

#include <syslog.h>

namespace common {

  namespace Private {

//*****************************************************************************
    CSyslogSpooler::CSyslogSpooler( const char* f_ProgramName ) {
      openlog( f_ProgramName, 0, LOG_USER );
    }
//*****************************************************************************
    CSyslogSpooler::~CSyslogSpooler() {
      closelog();
    }
//*****************************************************************************
    const ELogSpooler::TYPE CSyslogSpooler::Type() const {
      return ELogSpooler::eSyslog;
    }
//*****************************************************************************
    void CSyslogSpooler::Out( const ELogLevel::LEVEL& f_Level,
        const char* f_Format, va_list f_List ) {
      if( 0L != f_List )
        vsyslog( f_Level, f_Format, f_List );
      else
        syslog( f_Level, "%s", f_Format );
    }
//*****************************************************************************
    CLogSpooler* CSyslogSpooler::Create( const char* f_Param )
        throw( std::bad_alloc ) {
      const char* name = CSinglCommandLine::Instance()->ProgramName();
      return new CSyslogSpooler( name );
    }

  }; /* namespace Private */

}; /* namespace common */
