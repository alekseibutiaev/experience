//*****************************************************************************
//    Project : pu40
//       File : CEventObserver.cpp
// Created on : Mar 25, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <poll.h>

#include <vector>
#include <iterator>
#include <algorithm>

#include "CEventObserver.hpp"
#include "CPairEvent.hpp"

namespace io {

  namespace {

//*****************************************************************************
    class CFindEventFor {
    public:
      CFindEventFor( const CEventPtr& f_EventPtr ) :
          pvEvent( f_EventPtr ) {
      }
      bool operator()( const CEventPtr& f_Event ) const {
/*
        f_Event->Print();
        pvEvent->Print();
*/
        return f_Event->CheckEvent( *pvEvent );
    }
    private:
      CEventPtr pvEvent;
    };
//*****************************************************************************
    class CFindAction {
    public:
      bool operator()( const struct pollfd& f_Event ) const {
        return f_Event.revents != 0;
      }
    };
//*****************************************************************************
    class CNoticeTarget {
    public:
      CNoticeTarget( const struct pollfd& f_Action ) : pvAction( f_Action ) {
      }
      void operator()( const CEventPtr& f_Event ) const {
        f_Event->NoticeTarget( pvAction );
      }
    private:
      const struct pollfd& pvAction;
    };
//*****************************************************************************
    void PreparePolls( CPollArray& f_Polls, const CEventArray& f_EventArray ) {
      CEventArray::const_iterator end = f_EventArray.end();
      CEventArray::const_iterator iter = f_EventArray.begin();
      while( end != iter )
        (*iter++)->AddToPollArray( f_Polls );
    }

  }; /* namespace */

//*****************************************************************************
  CEventObserver::CEventObserver() :
      common::CClassName< CEventObserver >( __FUNCTION__ ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CEventObserver::~CEventObserver() {
    MEMBER_LOG;
  }
//*****************************************************************************
  bool CEventObserver::AddEvent( const CEventPtr& f_Event ) {
    MEMBER_LOG;
    CEventArray::iterator end = pvEventArray.end();
    CEventArray::iterator iter = std::find_if( pvEventArray.begin(),
        end, CFindEventFor( f_Event ) );
    if( iter == end ) {
      pvEventArray.push_back( f_Event );
      return true;
    }
    else
      common::Log()->Out( common::ELogLevel::eWarning, ClassName( this ),
          __FUNCTION__, "Event is not unique.\n");
    return true;
  }
//*****************************************************************************
  void CEventObserver::DelEvent( const CEventPtr& f_Event ) {
    MEMBER_LOG;
    CEventArray::iterator end = pvEventArray.end();
    CEventArray::iterator iter = std::find_if( pvEventArray.begin(),
        end, CFindEventFor( f_Event ) );
    if( end != iter )
      pvEventArray.erase( iter );
    else
      common::Log()->Out( common::ELogLevel::eWarning, ClassName( this ),
          __FUNCTION__, "Event is not exists.\n");
  }
//*****************************************************************************
  EObserver::RESULT CEventObserver::WaitEvents( const int& f_Timeout ) const {
    MEMBER_LOG;
    CPollArray polls;
    // fill pollfd array from array.
    CEventArray array( pvEventArray );
    PreparePolls( polls, array );
    common::Log()->Out( common::ELogLevel::eInfo, ClassName( this ),
        __FUNCTION__, "Poll array %d.\n", polls.size() );
    if( int res = poll( &polls[ 0 ], polls.size(), f_Timeout ) ) {
      if( res < 0 ) {
        // prepare error poll.
        ptStoreErrno();
        if( EINTR == ErrorNumber() )
          common::Log()->Out( common::ELogLevel::eErr, ClassName( this ),
              __FUNCTION__, "Polling has been interrupted by signal.\n");
        else
          common::Log()->Out( common::ELogLevel::eErr, ClassName( this ),
              __FUNCTION__, "Polling error.\n");
        return EObserver::eError;
      }
      else {
        common::Log()->Out( common::ELogLevel::eNotice, ClassName( this ),
            __FUNCTION__, "Detect %d events.\n", res );
        // find active events in pollfd arrays.
        CPollArray::const_iterator end = polls.end();
        CPollArray::const_iterator action = polls.begin();
        while( end != ( action = std::find_if( action, end, CFindAction() ) ) )
          // notice all target
          std::for_each( array.begin(), array.end(),
              CNoticeTarget( static_cast< const pollfd& >( *action++ ) ) );
        return EObserver::eOk;
      }
    }
    else
      common::Log()->Out( common::ELogLevel::eNotice, ClassName( this ),
          __FUNCTION__, "Timeout.\n");
    return EObserver::eTimeOut;
  }

}; /* namespace io */
