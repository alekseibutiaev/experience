//*****************************************************************************
//    Project : pu40
//       File : CPipe.cpp
// Created on : Sep 29, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <unistd.h>

#include <cerrno>

#include <new>

#include "iocommon.hpp"
#include "CDescriptor.hpp"
#include "CPairDescriptor.hpp"
#include "CPipe.hpp"

namespace io {
//  const char* CLASS_NAME = "CPipe";

//*****************************************************************************
  CPipe::CPipe() throw( std::runtime_error ) :
        common::CClassName< CPipe >( __FUNCTION__ ),
        pvParentProcess( INVALID_PID ) {
    MEMBER_LOG;
    // initialize descriptors of pipes.
    pvPipeA[ CPipe::eRead ] = io::INVALID_RESULT;
    pvPipeA[ CPipe::eWrite ] = io::INVALID_RESULT;
    pvPipeB[ CPipe::eRead ] = io::INVALID_RESULT;
    pvPipeB[ CPipe::eWrite ] = io::INVALID_RESULT;
    // created pipes channel
    if( io::INVALID_RESULT != pipe( pvPipeA ) &&
        io::INVALID_RESULT != pipe( pvPipeB ) ) {
      // get parent pid
      pvParentProcess = getpid();
      common::Log()->Out( common::ELogLevel::eInfo, ClassName( this ),
          __FUNCTION__, "Pipes has been created\n");
      return;
    }
    ptStoreErrno();
    common::Log()->Out( common::ELogLevel::eErr, ClassName( this ),
        __FUNCTION__, "Can not create pipe. Reason: %s\n", ErrorString() );
    Private::CloseDescriptor( pvPipeA[ CPipe::eRead ] );
    Private::CloseDescriptor( pvPipeA[ CPipe::eWrite ] );
    throw( std::runtime_error( ErrorString() ) );
  }
//*****************************************************************************
  CPipe::~CPipe() {
    MEMBER_LOG;
  }
//*****************************************************************************
  CDescriptorPtr CPipe::Server()  throw ( std::bad_alloc ) {
    MEMBER_LOG;
    assert( getpid() == pvParentProcess );
    // close unused descriptor.
    Private::CloseDescriptor( pvPipeA[ CPipe::eRead ] );
    Private::CloseDescriptor( pvPipeB[ CPipe::eWrite ] );
    return CDescriptorPtr( new CPairDescriptor( pvPipeB[ CPipe::eRead ],
        pvPipeA[ CPipe::eWrite ] ) );
  }
//*****************************************************************************
  CDescriptorPtr CPipe::Client()  throw ( std::bad_alloc ) {
    MEMBER_LOG;
    assert( getpid() != pvParentProcess );
    // close unused descriptor.
    Private::CloseDescriptor( pvPipeA[ CPipe::eWrite ] );
    Private::CloseDescriptor( pvPipeB[ CPipe::eRead ] );
    return CDescriptorPtr( new CPairDescriptor( pvPipeA[ CPipe::eRead ],
        pvPipeB[ CPipe::eWrite ] ) );
  }
//*****************************************************************************

}; /* namespace io */
