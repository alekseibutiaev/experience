//*****************************************************************************
//    Project : pu40
//       File : CRs485.cpp
// Created on : Jul 13, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <sys/ioctl.h>

#include "CRs485.hpp"

namespace io {

  namespace {

#if defined( HOST_IS_I386 ) || defined( HOST_IS_X86_64 )

    class CWriteDirection {
    public:
      CWriteDirection( const int& f_Descriptor ) : pvDescriptor( f_Descriptor ) {
        int status;
        ioctl( pvDescriptor, TIOCMGET, &status );
        status |= TIOCM_RTS;
        ioctl( pvDescriptor, TIOCMSET, &status );
      }
      ~CWriteDirection() {
        int status;
        tcdrain( pvDescriptor );
        ioctl( pvDescriptor, TIOCMGET, &status );
        status &= ~TIOCM_RTS;
        ioctl( pvDescriptor, TIOCMSET, &status );
      }
    private:
      const int& pvDescriptor;
    };
#elif defined( HOST_IS_ARM )

    class CWriteDirection {
    public:
      CWriteDirection( const int& f_Descriptor ) : pvDescriptor( f_Descriptor ) {
        int status;
        ioctl( pvDescriptor, TIOCMGET, &status );
        status &= ~TIOCM_RTS;
        ioctl( pvDescriptor, TIOCMSET, &status );
      }
      ~CWriteDirection() {
        int status;
        tcdrain( pvDescriptor );
        ioctl( pvDescriptor, TIOCMGET, &status );
        status |= TIOCM_RTS;
        ioctl( pvDescriptor, TIOCMSET, &status );
      }
    private:
      const int& pvDescriptor;
    };
#else
#warning "Unsupported host."
#endif
  }; /* namespace */

//*****************************************************************************
  CRs485::CRs485() : common::CClassName< CRs485 >( __FUNCTION__ ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CRs485::CRs485( const char* f_Name, const EAccess::MODE& f_Mode,
      bool f_Noctty ) throw ( std::runtime_error ) :
      CSerial( f_Name, f_Mode, f_Noctty ),
      common::CClassName< CRs485 >( __FUNCTION__ ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CRs485::~CRs485() {
    MEMBER_LOG;
  }
//*****************************************************************************
  long CRs485::Write( const void* f_Buf, unsigned long f_Size ) {
    MEMBER_LOG;
    CWriteDirection wd( ptEvent->Descriptor() );
    return CSerial::Write( f_Buf, f_Size );
  }

}; /* namespace io */
