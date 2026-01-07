//*****************************************************************************
//    Project : pu40
//       File : CFifoDescriptor.cpp
// Created on : Nov 25, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru 
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <sys/types.h>  // for open
#include <sys/stat.h>   // for open
#include <fcntl.h>      // for open

#include "iocommon.hpp"
#include "CFifoDescriptor.hpp"

namespace io {

//*****************************************************************************
  CFifoDescriptor::CFifoDescriptor( int f_Read, int f_Write ) :
      CPairDescriptor( f_Read, f_Write ),
      common::CClassName< CFifoDescriptor >( __FUNCTION__ ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CFifoDescriptor::CFifoDescriptor( int f_Read,
        const std::string& f_WriteName ) :
      CPairDescriptor( f_Read, io::INVALID_DESCRIPTOR ),
      common::CClassName< CFifoDescriptor >( __FUNCTION__ ),
      pvName( f_WriteName ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CFifoDescriptor::~CFifoDescriptor() {
    MEMBER_LOG;
  }
//*****************************************************************************
  long CFifoDescriptor::Write( const void* f_Buf, unsigned long f_Size ) {
    MEMBER_LOG;
    // Check up current descriptor.
    if( io::INVALID_DESCRIPTOR == PairEvent()->DescriptorWrite() ) {
      int wd = io::INVALID_DESCRIPTOR;
      if( !pvName.empty() && io::INVALID_DESCRIPTOR == ( wd =
            open( pvName.c_str(), O_WRONLY | O_NONBLOCK, 0 ) ) ) {
        ptResetErrno( errno );
        common::Log()->Out( common::ELogLevel::eCrit, ClassName( this ),
            __FUNCTION__, "Can not create fifo for write. Reason: %s\n",
            ErrorString() );
        return io::INVALID_RESULT;
      }
      ptNonBlock( wd, ptWriteNonBlock );
      // store descriptor for write
      PairEvent()->DescriptorWrite() = wd;
    }
    return CPairDescriptor::Write( f_Buf, f_Size );
  }

}; /* namespace io */
