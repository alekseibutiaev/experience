//*****************************************************************************
//    Project : pu40
//       File : CConsoleSpooler.cpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include "CConsoleSpooler.hpp"

#include <cstdio>

namespace common {

  namespace Private {

//*****************************************************************************
    CConsoleSpooler::CConsoleSpooler() {
    }
//*****************************************************************************
    CConsoleSpooler::~CConsoleSpooler() {
    }
//*****************************************************************************
    void CConsoleSpooler::Out( const ELogLevel::LEVEL& f_Level,
        const char* f_Format, va_list f_List ) {
      FILE* out = f_Level < ELogLevel::eWarning ? stderr : stdout;
      if( 0L != f_List )
        vfprintf( out, f_Format, f_List );
      else
        fputs( f_Format, out );
    }
//*****************************************************************************
    const ELogSpooler::TYPE CConsoleSpooler::Type() const{
      return ELogSpooler::eConsole;
    }
//*****************************************************************************
    CLogSpooler* CConsoleSpooler::Create(  const char* f_Param )
        throw( std::bad_alloc ) {
      return new CConsoleSpooler();
    }

  }; /* namespace Private */

}; /* namespace common */
