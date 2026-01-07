//*****************************************************************************
//    Project : pu40
//       File : CPairDescriptor.cpp
// Created on : Apr 14, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <unistd.h>

#include <cassert>
#include <iostream>

#include "iocommon.hpp"
#include "CPairEvent.hpp"
#include "CPairDescriptor.hpp"

namespace io {

//*****************************************************************************
  CPairDescriptor::CPairDescriptor() :
      CDescriptor( new CPairEvent() ),
      common::CClassName< CPairDescriptor >( __FUNCTION__ ),
      ptWriteNonBlock( true ), ptReadNonBlock( true ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CPairDescriptor::CPairDescriptor( int f_Read, int f_Write ) :
      CDescriptor( new CPairEvent() ),
      common::CClassName< CPairDescriptor >( __FUNCTION__ ),
      ptWriteNonBlock( true ), ptReadNonBlock( true ) {
    MEMBER_LOG;
    PairEvent()->Descriptor()= f_Read;
    PairEvent()->DescriptorWrite() = f_Write;
  }

//*****************************************************************************
  CPairDescriptor::~CPairDescriptor() {
    MEMBER_LOG;
    Private::CloseDescriptor( PairEvent()->DescriptorWrite() );
  }
//*****************************************************************************
  long CPairDescriptor::Write( const void* f_Buf, unsigned long f_Size ) {
    MEMBER_LOG;
    return ptWrite( PairEvent()->DescriptorWrite(), f_Buf, f_Size );
  }
//*****************************************************************************
  long CPairDescriptor::Read( void* f_Buf, unsigned long f_Size ) {
    MEMBER_LOG;
    return ptRead( ptEvent->Descriptor(), f_Buf, f_Size );
  }
//*****************************************************************************
  bool CPairDescriptor::NonBlock( bool f_OnOff ) {
    MEMBER_LOG;
    bool wr = true;
    bool rd = true;
    if( io::INVALID_DESCRIPTOR == PairEvent()->DescriptorWrite() )
      ptWriteNonBlock = f_OnOff;
    else if( !( wr = ptNonBlock( PairEvent()->DescriptorWrite(), f_OnOff ) ) )
        assert( false );
    if( io::INVALID_DESCRIPTOR == PairEvent()->Descriptor() )
      ptReadNonBlock = f_OnOff;
    else if( !( rd = ptNonBlock( ptEvent->Descriptor(), f_OnOff ) ) )
      assert( false );
    return wr && rd;
  }
//*****************************************************************************
  common::EThreeState::STATE CPairDescriptor::IsNonBlockWrite() {
    MEMBER_LOG;
    return ptIsNonBlock( PairEvent()->DescriptorWrite() );
  }
//*****************************************************************************
  CPairEvent* CPairDescriptor::PairEvent() {
    MEMBER_LOG;
    return static_cast< CPairEvent* >( &(*Event()) );
  }
//*****************************************************************************
  bool CPairDescriptor::MakeServer() {
    MEMBER_LOG;
    return true;
  }
//*****************************************************************************
  bool CPairDescriptor::MakeClient() {
    MEMBER_LOG;
    return true;
  }
}
