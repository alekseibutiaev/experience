//*****************************************************************************
//    Project : pu40
//       File : CPairEvent.cpp
// Created on : Apr 15, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include "iocommon.hpp"
#include "CPairDescriptor.hpp"
#include "EAction.hpp"

#include "CPairEvent.hpp"

namespace io {

//*****************************************************************************
  CPairEvent::CPairEvent() :
      common::CClassName< CPairEvent >( __FUNCTION__ ) {
    MEMBER_LOG;
    pvPollfdWrite.fd = INVALID_DESCRIPTOR;
    pvPollfdWrite.events = 0;
    pvPollfdWrite.revents = 0;
  }
//*****************************************************************************
  CPairEvent::~CPairEvent() {
    MEMBER_LOG;
  }
//*****************************************************************************
  int& CPairEvent::DescriptorWrite() {
    MEMBER_LOG;
    return pvPollfdWrite.fd;
  }
//*****************************************************************************
  const int& CPairEvent::DescriptorWrite() const {
    MEMBER_LOG;
    return pvPollfdWrite.fd;
  }
//*****************************************************************************
  CEvent& CPairEvent::WaitEnable( const EAction::TYPE& f_Action ) {
    MEMBER_LOG;
    if( EAction::eWriteNormal == f_Action )
      pvPollfdWrite.events |= ToPosix( f_Action );
    else
      CEvent::WaitEnable( f_Action );
    return *this;
  }
//*****************************************************************************
  CEvent& CPairEvent::WaitDisable( const EAction::TYPE& f_Action ) {
    MEMBER_LOG;
    if( EAction::eWriteNormal == f_Action )
      pvPollfdWrite.events &= ~ToPosix( f_Action );
    else
      CEvent::WaitDisable( f_Action );
    return *this;
  }
//*****************************************************************************
  CEvent& CPairEvent::ResetAllWaitings() {
    MEMBER_LOG;
    pvPollfdWrite.events = 0;
    CEvent::ResetAllWaitings();
    return *this;
  }
//*****************************************************************************
  CPairEvent* CPairEvent::Clone() const {
    MEMBER_LOG;
    return new CPairEvent( *this );
  }
//*****************************************************************************
  void CPairEvent::AddToPollArray( CPollArray& f_PollArray ) const {
    MEMBER_LOG;
    // To add both descriptors.
    ptAddToPollArray( f_PollArray, pvPollfdWrite );
    CEvent::AddToPollArray( f_PollArray );
  }
//*****************************************************************************
  void CPairEvent::NoticeTarget( const struct pollfd& f_ActiveFlag ) const {
    MEMBER_LOG;
    if( pvPollfdWrite.fd == f_ActiveFlag.fd )
      ptNoticeTarget( f_ActiveFlag );
    else
      CEvent::NoticeTarget( f_ActiveFlag );
  }
//*****************************************************************************
  bool CPairEvent::CheckAction( const EAction::TYPE& f_Action ) const {
    MEMBER_LOG;
    return 0 == ( pvPollfdWrite.revents & ToPosix( f_Action ) ) ||
      CEvent::CheckAction( f_Action );
  }
//*****************************************************************************
  bool CPairEvent::CheckEvent( const CEvent& f_Event ) const {
    MEMBER_LOG;
    bool result = false;
    // detect CPairEvent
    if( const CPairEvent* pairevent = dynamic_cast< const CPairEvent* >( &f_Event ) )
      result = pairevent->DescriptorWrite() != io::INVALID_DESCRIPTOR &&
          ( pairevent->DescriptorWrite() == DescriptorWrite() ||
          pairevent->DescriptorWrite() == Descriptor() ) ;
    result = result || ( f_Event.Descriptor() != io::INVALID_DESCRIPTOR &&
        ( f_Event.Descriptor() == Descriptor() ||
        f_Event.Descriptor() == DescriptorWrite() ) );
    return result;
  }
//*****************************************************************************
  void CPairEvent::Print() const {
    MEMBER_LOG;
    std::cout << "Write descriptor " << pvPollfdWrite.fd << " Event " <<
        pvPollfdWrite.events << std::endl;
    CEvent::Print();
  }

}; /* namespace io */
