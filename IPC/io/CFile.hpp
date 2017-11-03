//*****************************************************************************
//    Project : pu40
//       File : CFile.hpp
// Created on : Mar 4, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CFILE_HPP__
#define __CFILE_HPP__

#include "common/common.hpp"

#include "iocommon.hpp"
#include "CDescriptor.hpp"

#include <stdexcept>

namespace io {

  class CFile :
      public CDescriptor,
      private common::CClassName< CFile > {
  public:
    CFile();
    // open file
    CFile( const char* f_PathName, const EAccess::MODE& f_Access,
        bool f_Append = false ) throw( std::runtime_error );
    // create file
    CFile( const char* f_PathName, const ECreate::MODE& f_Create )
        throw( std::runtime_error );
    ~CFile();
    bool Open( const char* f_PathName, const EAccess::MODE& f_Access,
        bool f_Append = false );
    bool Create( const char* f_PathName, const ECreate::MODE& f_Create );
    CFile* Clone() throw( std::bad_alloc );
  };

}; /* namespace io */

#endif /* __CFILE_HPP__ */
