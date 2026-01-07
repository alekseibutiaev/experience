 //*****************************************************************************
//    Project : pu40
//       File : CFile.cpp
// Created on : Mar 4, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <sys/types.h>
#include <fcntl.h>

#include <cassert>
#include <cerrno>
#include <cstring>

#include "CFile.hpp"

namespace io {

//*****************************************************************************
  CFile::CFile() :
      common::CClassName< CFile >( __FUNCTION__ ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CFile::CFile( const char* f_PathName, const EAccess::MODE& f_Access,
      bool f_Append ) throw( std::runtime_error ) :
      common::CClassName< CFile >( __FUNCTION__ ) {
    MEMBER_LOG;
    if( !Open( f_PathName, f_Access, f_Append ) )
      throw( std::runtime_error( ErrorString() ) );
  }
//*****************************************************************************
  CFile::CFile( const char* f_PathName, const ECreate::MODE& f_Create )
      throw( std::runtime_error ) : common::CClassName< CFile >( __FUNCTION__ ) {
    MEMBER_LOG;
    if( !Create( f_PathName, f_Create ) )
      throw( std::runtime_error( ErrorString() ) );
  }
//*****************************************************************************
  CFile::~CFile() {
    MEMBER_LOG;
  }
//*****************************************************************************
  bool CFile::Open( const char* f_PathName, const EAccess::MODE& f_Access,
      bool f_Append ) {
    MEMBER_LOG;
    if( INVALID_DESCRIPTOR == ( ptEvent->Descriptor() = open( f_PathName,
        Private::AccessModeToPosix( f_Access ) | f_Append ? O_APPEND : 0 ) ) ) {
      ptStoreErrno();
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "File \"%s\" not opened. Reason: %s\n", f_PathName,
          ErrorString() );
      return false;
    }
    return true;
  }
//*****************************************************************************
  bool CFile::Create( const char* f_PathName, const ECreate::MODE& f_Create ){
    MEMBER_LOG;
    if( INVALID_DESCRIPTOR == ( ptEvent->Descriptor() = creat( f_PathName,
        Private::CreateModeToPosix( f_Create ) ) ) ) {
      ptStoreErrno();
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "File %s not created. Reason: %s\n", f_PathName,
          ErrorString() );
      return false;
    }
    return true;
  }
//*****************************************************************************
  CFile* CFile::Clone() throw( std::bad_alloc ) {
    MEMBER_LOG;
    return new CFile();
  }


} ; /* namespace io */
