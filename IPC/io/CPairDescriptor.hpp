//*****************************************************************************
//    Project : pu40
//       File : CPairDescriptor.hpp
// Created on : Apr 14, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CPAIRDESCRIPTOR_HPP__
#define __CPAIRDESCRIPTOR_HPP__

#include <new>

#include "CDescriptor.hpp"
#include "CPairEvent.hpp"

namespace io {

  class CPairDescriptor :
      public CDescriptor,
      private common::CClassName< CPairDescriptor > {
  public:
    CPairDescriptor( int f_Read, int f_Write );
    virtual ~CPairDescriptor();
    virtual long Write( const void* f_Buf, unsigned long f_Size );
    virtual long Read( void* f_Buf, unsigned long f_Size );
    virtual bool NonBlock( bool f_OnOff );
    virtual common::EThreeState::STATE IsNonBlockWrite();
    CPairEvent* PairEvent();
    virtual bool MakeServer();
    virtual bool MakeClient();
  protected:
    CPairDescriptor();
  protected:
    bool ptWriteNonBlock;
    bool ptReadNonBlock;
  };

  typedef boost::shared_ptr< CPairDescriptor > CPairDescriptorPtr;
}

#endif /* __CPAIRDESCRIPTOR_HPP__ */
