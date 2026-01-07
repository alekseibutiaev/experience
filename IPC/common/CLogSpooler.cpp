//*****************************************************************************
//    Project : pu40
//       File : CLogSpooler.cpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include "CLogSpooler.hpp"

#include "CMemorySpooler.hpp"
#include "CConsoleSpooler.hpp"
#include "CFileSpooler.hpp"
#include "CSyslogSpooler.hpp"


namespace common {

  namespace Private {

//*****************************************************************************
    static FCreateSpooler create[] = {
        CConsoleSpooler::Create,
        CSyslogSpooler::Create,
        CFileSpooler::Create,
        CMemorySpooler::Create
    };

//*****************************************************************************
    CLogSpooler::CLogSpooler() {
    }
//*****************************************************************************
    CLogSpooler::~CLogSpooler() {
    }
//*****************************************************************************
    CLogSpooler* CLogSpooler::Create( const ELogSpooler::TYPE& f_Type,
        const char* f_Param ) throw( std::bad_alloc ) {
      return f_Type < ELogSpooler::eUnknown ? create[ f_Type ]( f_Param ) : 0L;
    }

  }; /* namespace Private */

}; /* namespace common */
