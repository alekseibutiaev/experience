//*****************************************************************************
//    Project : pu40
//       File : CFileSpooler.cpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include "CFileSpooler.hpp"

#include <cstdio>
#include <iostream>
#include <new>

namespace common {

  namespace Private {

//*****************************************************************************
    CFileSpooler::CFileSpooler( const char* f_Param ) {
      if( !( pvOut = fopen( f_Param, "w" ) ) ) {
        std::cerr << "The file for log out has not been created." << std::endl;
        throw( std::bad_alloc() );
      }
    }
//*****************************************************************************
    CFileSpooler::~CFileSpooler() {
      fclose( pvOut );
    }
//*****************************************************************************
    void CFileSpooler::Out( const ELogLevel::LEVEL& f_Level,
        const char* f_Format, va_list f_List ) {
      if( 0L != f_List )
        vfprintf( pvOut, f_Format, f_List );
      else
        fputs( f_Format, pvOut );
    }
//*****************************************************************************
    const ELogSpooler::TYPE CFileSpooler::Type() const {
      return ELogSpooler::eFile;
    }
//*****************************************************************************
    CLogSpooler* CFileSpooler::Create( const char* f_Param )
        throw( std::bad_alloc ) {
      return new CFileSpooler( f_Param );
    }

  }; /* namespace Private */

} /* namespace common */
