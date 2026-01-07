//*****************************************************************************
//    Project : pu40
//       File : IEventTarget.cpp
// Created on : Mar 25, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include "CEvent.hpp"

namespace io {

//*****************************************************************************
  CEventTarget::CEventTarget() :
        common::CClassName< CEventTarget >( __FUNCTION__ ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CEventTarget::~CEventTarget() {
    MEMBER_LOG;
  }
//*****************************************************************************
  EOrder::MODE CEventTarget::ReadNormal( const CEvent& f_Action ) {
    MEMBER_LOG;
    return EOrder::eNext;
  }
//*****************************************************************************
  EOrder::MODE CEventTarget::ReadPriority( const CEvent& f_Action ) {
    MEMBER_LOG;
    return EOrder::eNext;
  }
//*****************************************************************************
  EOrder::MODE CEventTarget::WriteNormal( const CEvent& f_Action ) {
    MEMBER_LOG;
    return EOrder::eNext;
  }
//*****************************************************************************
  EOrder::MODE CEventTarget::ErrorCondition( const CEvent& f_Action ) {
    MEMBER_LOG;
    return EOrder::eNext;
  }
//*****************************************************************************
  EOrder::MODE CEventTarget::ErrorHungUp( const CEvent& f_Action ) {
    MEMBER_LOG;
    return EOrder::eNext;
  }
//*****************************************************************************
  EOrder::MODE CEventTarget::ErrorRequest( const CEvent& f_Action ) {
    MEMBER_LOG;
    return EOrder::eNext;
  }
//*****************************************************************************
  void CEventTarget::Notice( const CEvent& f_Action ) {
    MEMBER_LOG;
    if( f_Action.CheckAction( io::EAction::eErrorRequest ) &&
          EOrder::eStop == ErrorRequest( f_Action ) )
      return;
    if( f_Action.CheckAction( io::EAction::eErrorHungUp ) &&
          EOrder::eStop == ErrorHungUp( f_Action ) )
      return;
    if( f_Action.CheckAction( io::EAction::eErrorCondition ) &&
          EOrder::eStop == ErrorCondition( f_Action ) )
      return;
    if( f_Action.CheckAction( io::EAction::eWriteNormal ) &&
          EOrder::eStop == WriteNormal( f_Action ) )
      return;
    if( f_Action.CheckAction( io::EAction::eReadPriority ) &&
          EOrder::eStop == ReadPriority( f_Action ) )
      return;
    if( f_Action.CheckAction( io::EAction::eReadNornal ) &&
          EOrder::eStop == ReadNormal( f_Action ) )
      return;
  }
}; /* namespace io */
