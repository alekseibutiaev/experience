//*****************************************************************************
//    Project : pu40
//       File : CEvent.cpp
// Created on : Mar 24, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <new>
#include <cassert>
#include <algorithm>

#include <common/common.hpp>
#include "iocommon.hpp"

#include "CPairEvent.hpp"

#include "CEvent.hpp"

namespace io {

//*****************************************************************************
  CEvent::CEvent() :
      common::CClassName< CEvent >( __FUNCTION__ ) {
    MEMBER_LOG;
    pvPollfd.fd = INVALID_DESCRIPTOR;
    pvPollfd.events = 0;
    pvPollfd.revents = 0;
  }
//*****************************************************************************
  CEvent::CEvent( const struct pollfd& f_Pollfd ) :
      common::CClassName< CEvent >( __FUNCTION__ ),
      pvPollfd( f_Pollfd ) {
    MEMBER_LOG;
//    pvPollfd = f_Pollfd;
  }
//*****************************************************************************
  CEvent::~CEvent() {
    MEMBER_LOG;
  }
//*****************************************************************************
  int& CEvent::Descriptor() {
    MEMBER_LOG;
    return pvPollfd.fd;
  }
//*****************************************************************************
  const int& CEvent::Descriptor() const {
    MEMBER_LOG;
    return pvPollfd.fd;
  }
//*****************************************************************************
  void CEvent::Target( CEventTargetPtr f_Target ) {
    MEMBER_LOG;
    pvTargetPtr = f_Target;
  }
//*****************************************************************************
  CEvent& CEvent::WaitEnable( const EAction::TYPE& f_Action ) {
    MEMBER_LOG;
    pvPollfd.events |= ToPosix( f_Action );
    return *this;
  }
//*****************************************************************************
  CEvent& CEvent::WaitDisable( const EAction::TYPE& f_Action ) {
    MEMBER_LOG;
    pvPollfd.events &= ~ToPosix( f_Action );
    return *this;
  }
//*****************************************************************************
  CEvent& CEvent::ResetAllWaitings() {
    MEMBER_LOG;
    pvPollfd.events = 0;
    return *this;
  }
//*****************************************************************************
  CEvent* CEvent::Clone() const {
    MEMBER_LOG;
    return new CEvent( *this );
  }
//*****************************************************************************
  void CEvent::AddToPollArray( CPollArray& f_PollfdArray ) const {
    MEMBER_LOG;
    return ptAddToPollArray( f_PollfdArray, pvPollfd );
  }
//*****************************************************************************
  void CEvent::NoticeTarget( const struct pollfd& f_ActiveFlag ) const {
    MEMBER_LOG;
    if( pvPollfd.fd == f_ActiveFlag.fd )
      ptNoticeTarget( f_ActiveFlag );
  }
//*****************************************************************************
  bool CEvent::CheckAction( const EAction::TYPE& f_Action ) const {
    MEMBER_LOG;
    return pvPollfd.revents & ToPosix( f_Action );
  }
//*****************************************************************************
  bool CEvent::CheckEvent( const CEvent& f_Event ) const {
    MEMBER_LOG;
    bool result = false;
    // detect CPairEvent
    if( const CPairEvent* pairevent =
        dynamic_cast< const CPairEvent* >( &f_Event ) ) {
      result = pairevent->DescriptorWrite() != io::INVALID_DESCRIPTOR &&
          pairevent->DescriptorWrite() == Descriptor();
    }
    result = f_Event.Descriptor() != io::INVALID_DESCRIPTOR &&
        ( result || f_Event.Descriptor() == Descriptor() );
    return result;
  }
//*****************************************************************************
  void CEvent::Print() const {
    MEMBER_LOG;
    std::cout << "Read descriptor " << pvPollfd.fd << " Event " <<
        pvPollfd.events << std::endl;
  }
//*****************************************************************************
  void CEvent::ptAddToPollArray( CPollArray& f_PollArray,
      const struct pollfd& f_Polfd ) const {
    MEMBER_LOG;
    // Add valid descriptor only.
    if( io::INVALID_DESCRIPTOR != f_Polfd.fd ) {
      // check up exists descriptor.
      CPollArray::iterator end = f_PollArray.end();
      if( end == std::search( f_PollArray.begin(), end, &f_Polfd, &f_Polfd + 1,
          CompareDescriptor ) ) {
        f_PollArray.push_back( f_Polfd );
        return;
      }
      common::Log()->Out( common::ELogLevel::eWarning, ClassName( this ),
          __FUNCTION__, "Event has been exists.\n");
    }
    else
      common::Log()->Out( common::ELogLevel::eNotice, ClassName( this ),
          __FUNCTION__, "To try addition invalid descriptor in"
          " to poll request.\n");
  }
//*****************************************************************************
  void CEvent::ptNoticeTarget( const struct pollfd& f_ActiveFlag ) const {
    MEMBER_LOG;
    try {
      CEventTargetPtr target( pvTargetPtr );
      target->Notice( CEvent( f_ActiveFlag ) );
    }
    catch( boost::bad_weak_ptr ) {
      common::Log()->Out( common::ELogLevel::eWarning, ClassName( this ),
          __FUNCTION__, "The target is not set or is not accessible.\n");
    }
  }
//*****************************************************************************
//*****************************************************************************
  inline bool CompareDescriptor( const pollfd& f_Left, const pollfd& f_Right ) {
    return f_Left.fd == f_Right.fd;
  }

}; /* namespace io */
