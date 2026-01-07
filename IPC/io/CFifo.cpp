//*****************************************************************************
//    Project : pu40
//       File : CFifo.cpp
// Created on : Sep 29, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <errno.h>

#include <sys/types.h>  // for open
#include <sys/stat.h>   // for open
#include <fcntl.h>      // for open

#include <cstring> // for mkfifo
#include <new> // for mkfifo

#include "CDescriptor.hpp"
#include "CPairDescriptor.hpp"
#include "CFifoDescriptor.hpp"

#include "CFifo.hpp"

namespace io {

  const char* const FIFO_PATH = "/tmp/";
  const char* const READ_SUFFIX = ".r";
  const char* const WRITE_SUFFIX = ".w";

//*****************************************************************************
  CFifoDescriptor* FifoServer( const std::string& f_WriteName,
      const std::string& f_ReadName, int& f_Errno )
        throw( std::bad_alloc, std::runtime_error ) {
    FUNCTION_LOG;
    int rd = io::INVALID_DESCRIPTOR;
    if( io::INVALID_DESCRIPTOR ==
          ( rd = open( f_ReadName.c_str(), O_RDONLY | O_NONBLOCK, 0 ) ) ) {
      f_Errno = errno;
      common::Log()->Out( common::ELogLevel::eCrit, __FILE__, __FUNCTION__,
          "Can not opening FIFO channel. Reason: %s.\n", strerror( f_Errno ) );
      throw( std::runtime_error( strerror( f_Errno ) ) );
    }
    return new CFifoDescriptor( rd, f_WriteName );
  }
//*****************************************************************************
  CFifoDescriptor* FifoClient( const std::string& f_WriteName,
      const std::string& f_ReadName, int& f_Errno )
        throw( std::bad_alloc, std::runtime_error ) {
    FUNCTION_LOG;
    int wd = io::INVALID_DESCRIPTOR;
    int rd = io::INVALID_DESCRIPTOR;
    if( io::INVALID_DESCRIPTOR ==
            ( wd = open( f_WriteName.c_str(), O_WRONLY | O_NONBLOCK, 0 ) ) ||
        io::INVALID_DESCRIPTOR ==
            ( rd = open( f_ReadName.c_str(), O_RDONLY | O_NONBLOCK, 0 ) ) ) {
      f_Errno = errno;
      Private::CloseDescriptor( wd );
      common::Log()->Out( common::ELogLevel::eCrit, __FILE__, __FUNCTION__,
          "Can not opening FIFO channel. Reason: %s.\n", strerror( f_Errno ) );
      throw( std::runtime_error( strerror( f_Errno ) ) );
    }
    return new CFifoDescriptor( rd, wd );
  }
//*****************************************************************************
  CFifo::CFifo( const std::string& f_Name, ECreate::MODE f_Mode )
        throw( std::runtime_error ) :
      common::CClassName< CFifo >( __FUNCTION__ ), pvIsServer( false ) {
    MEMBER_LOG;
    if( !f_Name.empty() && !Name( f_Name, f_Mode ) )
      throw( std::runtime_error( ErrorString() ) );
  }
//*****************************************************************************
  CFifo::~CFifo() {
    MEMBER_LOG;
    if( pvIsServer && !pvWriteName.empty() && !pvReadName.empty() ) {
      unlink( pvWriteName.c_str() );
      unlink( pvReadName.c_str() );
    }
  }
//*****************************************************************************
  bool CFifo::Name( const std::string& f_Name, ECreate::MODE f_Mode ) {
    MEMBER_LOG;
    assert( pvWriteName.empty() && pvReadName.empty() );
    int mode = Private::CreateModeToPosix( f_Mode );
    pvWriteName = FIFO_PATH + f_Name + WRITE_SUFFIX;
    pvReadName = FIFO_PATH + f_Name + READ_SUFFIX;
    return pvCreateNods( pvWriteName, mode ) && pvCreateNods( pvReadName, mode );
  }
//*****************************************************************************
  CDescriptorPtr CFifo::Server() throw ( std::bad_alloc, std::runtime_error ) {
    MEMBER_LOG;
    assert( !pvWriteName.empty() && !pvReadName.empty() );
    pvIsServer = true;
    int err = 0;
    CDescriptor* descriptor = FifoServer( pvWriteName, pvReadName, err );
    ptResetErrno( err );
    return CDescriptorPtr( descriptor );
  }
//*****************************************************************************
  CDescriptorPtr CFifo::Client() throw ( std::bad_alloc, std::runtime_error ) {
    MEMBER_LOG;
    assert( !pvWriteName.empty() && !pvReadName.empty() );
    int err = 0;
    CDescriptor* descriptor = FifoClient( pvReadName, pvWriteName, err );
    ptResetErrno( err );
    return CDescriptorPtr( descriptor );
  }
//*****************************************************************************
  bool CFifo::pvCreateNods( const std::string& f_Name, int f_Mode ) {
    MEMBER_LOG;
    if( INVALID_RESULT == mkfifo( f_Name.c_str(), f_Mode ) &&
        EEXIST != ptStoreErrno() ) {
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Fifo channel has not been created. Reason: %s.\n",
          ErrorString() );
      return false;
    }
    // reset exist error
    ptResetErrno();
    common::Log()->Out( common::ELogLevel::eInfo, common::ClassName( this ),
        __FUNCTION__, "Node for fifo channel has been created.\n" );
    return true;
  }

}; /* namespace io */
