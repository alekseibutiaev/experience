//*****************************************************************************
//    Project : pu40
//       File : CDescriptor.cpp
// Created on : Mar 4, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <unistd.h>
#include <fcntl.h>

#include <cstring>

#include "iocommon.hpp"
#include "CDescriptor.hpp"

namespace io {

//*****************************************************************************
  CDescriptor::CDescriptor() :
      common::CClassName< CDescriptor >( __FUNCTION__ ),
      ptRestart( false ),
      ptEvent( new CEvent ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CDescriptor::CDescriptor( CEvent* f_Event ) :
      common::CClassName< CDescriptor >( __FUNCTION__ ),
      ptRestart( false ),
      ptEvent( f_Event ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CDescriptor::~CDescriptor() {
    MEMBER_LOG;
    Private::CloseDescriptor( ptEvent->Descriptor() );
  }
//*****************************************************************************
  long CDescriptor::Write( const void* f_Buf, unsigned long f_Size ) {
    MEMBER_LOG;
    return ptWrite( ptEvent->Descriptor(), f_Buf, f_Size );
  }
//*****************************************************************************
  long CDescriptor::Read( void* f_Buf, unsigned long f_Size ) {
    MEMBER_LOG;
    return ptRead( ptEvent->Descriptor(), f_Buf, f_Size );
  }
//*****************************************************************************
  bool CDescriptor::NonBlock( bool f_OnOff ) {
    MEMBER_LOG;
    return ptNonBlock( ptEvent->Descriptor(), f_OnOff );
  }
//*****************************************************************************
  common::EThreeState::STATE CDescriptor::IsNonBlock() {
    MEMBER_LOG;
    return ptIsNonBlock( ptEvent->Descriptor() );
  }
//*****************************************************************************
  CEventPtr CDescriptor::Event() {
    MEMBER_LOG;
    return ptEvent;
  }
//*****************************************************************************
  bool& CDescriptor::AutoRestart() {
    MEMBER_LOG;
    return ptRestart;
  }
//*****************************************************************************
  const bool& CDescriptor::AutoRestart() const {
    MEMBER_LOG;
    return ptRestart;
  }
//*****************************************************************************
  long CDescriptor::ptWrite( int& f_Desctiptor, const void* f_Buf,
      unsigned long f_Size ) {
    MEMBER_LOG;
    assert( INVALID_DESCRIPTOR != f_Desctiptor );
    long result;
    while( INVALID_RESULT == ( result = write( f_Desctiptor, f_Buf, f_Size ) )
        && EINTR == ptStoreErrno() && ptRestart ) {
      ptResetErrno();
      common::Log()->Out( common::ELogLevel::eNotice, common::ClassName( this ),
          __FUNCTION__, "System call has been interrupted.\n" );
    }
    common::Log()->Out( common::ELogLevel::eDebug, common::ClassName( this ),
        __FUNCTION__, "%d bytes has been write.\n", result );
    if( INVALID_RESULT == result )
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Write to file is failure.\n" );
    return result;
  }
//*****************************************************************************
  long CDescriptor::ptRead( int& f_Desctiptor, void* f_Buf,
      unsigned long f_Size ) {
    MEMBER_LOG;
    assert( INVALID_DESCRIPTOR != f_Desctiptor );
    long result;
    while( INVALID_RESULT == ( result = read( f_Desctiptor, f_Buf, f_Size ) )
        && EINTR == ptStoreErrno() && ptRestart ) {
      ptResetErrno();
      common::Log()->Out( common::ELogLevel::eNotice, common::ClassName( this ),
          __FUNCTION__, "System call has been interrupted.\n" );
    }
    common::Log()->Out( common::ELogLevel::eDebug, common::ClassName( this ),
        __FUNCTION__, "%d bytes has been read.\n", result );
    return result;
  }
//*****************************************************************************
  bool CDescriptor::ptNonBlock( int f_Desctiptor, bool f_OnOff  ){
    MEMBER_LOG;
    return ptChangeFlag( f_Desctiptor, f_OnOff, O_NONBLOCK );
  }
//*****************************************************************************
  common::EThreeState::STATE CDescriptor::ptIsNonBlock( int f_Desctiptor ) {
    MEMBER_LOG;
    int flags = ptGetFlags( f_Desctiptor );
    return (INVALID_RESULT == flags) ? common::EThreeState::eError :
      (0 == (flags & O_NONBLOCK)) ? common::EThreeState::eReset :
        common::EThreeState::eSet;
  }
//*****************************************************************************
  int CDescriptor::ptGetFlags( int f_Descriptor ) {
    MEMBER_LOG;
    assert( INVALID_DESCRIPTOR != f_Descriptor );
    int flags = fcntl( f_Descriptor, F_GETFL, 0 );
    if( INVALID_RESULT == flags ) {
      ptStoreErrno();
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Can not getting flags of descriptor.\n" );
    }
    return flags;
  }
//*****************************************************************************
  bool CDescriptor::ptChangeFlag( int f_Descriptor, bool f_OnOff, int f_Flags ) {
    MEMBER_LOG;
    assert( INVALID_DESCRIPTOR != f_Descriptor );
    int flags = ptGetFlags( f_Descriptor );
    if( INVALID_RESULT == flags )
      return false;
    flags = f_OnOff ? flags | f_Flags : flags & ~f_Flags;
    if( INVALID_RESULT == fcntl( f_Descriptor, F_SETFL, flags ) ) {
      ptStoreErrno();
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Can not setting flags of descriptor.\n" );
      return false;
    }
    return true;
  }
//*****************************************************************************

}; /* namespace io */
