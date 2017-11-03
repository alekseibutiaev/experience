//*****************************************************************************
//    Project : pu40
//       File : CSerial.cpp
// Created on : Mar 5, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

//#define USE_FUNCTION_LOGGER
#include <common/CFunctionLog.hpp>

#include <fcntl.h>


#include <cstring>
#include <iostream>

#include <common/common.hpp>
#include "CSerial.hpp"

namespace io {

  const int TERMIOS_ERROR = -1;

//*****************************************************************************
  CSerial::CSerial() :
        common::CClassName< CSerial >( __FUNCTION__ ) {
    MEMBER_LOG;
  }
//*****************************************************************************
  CSerial::CSerial( const char* f_Name, const EAccess::MODE& f_Mode,
      bool f_Noctty ) throw ( std::runtime_error ) :
      common::CClassName< CSerial >( __FUNCTION__ ) {
    MEMBER_LOG;
    if( !Open( f_Name, f_Mode, f_Noctty ) )
      throw( std::runtime_error( "Port has not been opened." ) );
  }
//*****************************************************************************
  CSerial::~CSerial() {
    MEMBER_LOG;
    // backup state of port
    if( TERMIOS_ERROR == tcsetattr( ptEvent->Descriptor(), TCSADRAIN,
        &pvTermBackup ) ) {
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Can not backup old port state.\n" );
    }
  }
//*****************************************************************************
  bool CSerial::Open( const char* f_Name, const EAccess::MODE& f_Mode,
      bool f_Noctty ) {
    MEMBER_LOG;
    // TODO: Add check type of file.
    int m1 = Private::AccessModeToPosix( f_Mode );
    int m2 = f_Noctty ? O_NOCTTY : 0;
    if( INVALID_DESCRIPTOR == ( ptEvent->Descriptor() = open( f_Name,
        m1 | m2 ) ) ) {
      ptStoreErrno();
      common::Log()->Out( common::ELogLevel::eCrit, common::ClassName( this ),
          __FUNCTION__, "The port %s has not been opened\n", f_Name );
      return false;
    }
    // backup state of port
    if( TERMIOS_ERROR == tcgetattr( ptEvent->Descriptor(), &pvTermBackup ) ) {
      ptStoreErrno();
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Can not backup old port state.\n", f_Name );
    }
    return true;
  }
//*****************************************************************************
  CSerial* CSerial::Clone() throw( std::bad_alloc ) {
    return new CSerial();
  }
//*****************************************************************************
  bool CSerial::SetSpeed( const ESpeed::TYPE& f_Speed ) {
    MEMBER_LOG;
    return ptChengAttribute( &CSerial::ptInputSpeed, &f_Speed ) &&
        ptChengAttribute( &CSerial::ptOutputSpeed, &f_Speed );
  }
//*****************************************************************************
  bool CSerial::GetSpeed( ESpeed::TYPE& f_Speed ) const {
    MEMBER_LOG;
    struct termios term;
    speed_t speed;
    if( !ptGetAttribute( &term ) )
      return false;
    if( ( speed = cfgetispeed( &term ) ) != cfgetospeed( &term ) ) {
      common::Log()->Out( common::ELogLevel::eWarning, common::ClassName( this ),
          __FUNCTION__, "Input and output speed it is different.\n" );
      return false;
    }
    f_Speed = ptPosixToSpeed( speed );
    return true;
  }
//*****************************************************************************
  bool CSerial::SetRawMode() {
    MEMBER_LOG;
    return ptChengAttribute( &CSerial::ptSetRawMode );
  }
//*****************************************************************************
  bool CSerial::ModemLine( const bool& f_Enable ) {
    MEMBER_LOG;
    return ptChengAttribute( &CSerial::ptModemLine, &f_Enable );
  }
//*****************************************************************************
  bool CSerial::ReadMode( const bool& f_Enable ) {
    MEMBER_LOG;
    return ptChengAttribute( &CSerial::ptReadMode, &f_Enable );
  }
//*****************************************************************************
  bool CSerial::HardWareFlow( const bool& f_Enable ) {
    MEMBER_LOG;
    return ptChengAttribute( &CSerial::ptHardWareFlow, &f_Enable );
  }
//*****************************************************************************
  bool CSerial::ptGetAttribute( struct termios* f_Attribute ) const {
    MEMBER_LOG;
    if( TERMIOS_ERROR == tcgetattr( ptEvent->Descriptor(), f_Attribute ) ) {
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Can not get current terminal attribute.\n" );
      return false;
    }
    return true;
  }
//*****************************************************************************
  bool CSerial::ptChengAttribute( ptSigChangeAttribute f_CangeFunction,
      const void* f_DataPtr ) {
    MEMBER_LOG;
    struct termios term;
    // Get current terminal attribute
    if( !ptGetAttribute( &term ) )
      return false;
    // backup current attribute
    struct termios backup = term;
    // take pointer to attribute.
    struct termios* termsetptr = &term;
    bool result;
    // apply change of attribute.
    if( !( result = (f_CangeFunction)( termsetptr, f_DataPtr ) ) ) {
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Can not change terminal attribute.\n" );
      // take pointer to backup attribute.
      termsetptr = &backup;
    }
    // set new attribute.
    if( TERMIOS_ERROR == tcsetattr( ptEvent->Descriptor(), TCSADRAIN,
        termsetptr ) ) {
      common::Log()->Out( common::ELogLevel::eErr, common::ClassName( this ),
          __FUNCTION__, "Can not changed speed of port.\n" );
      return false;
    }
    return result;
  }
//*****************************************************************************
  bool CSerial::ptInputSpeed( struct termios* f_Attribute,
      const void* f_DataPtr ) {
    const ESpeed::TYPE* f_SpeedPtr =
        reinterpret_cast< const ESpeed::TYPE* >( f_DataPtr );
    return TERMIOS_ERROR != cfsetispeed( f_Attribute,
        ptSpeedToPosix( *f_SpeedPtr ) );
  }
//*****************************************************************************
  bool CSerial::ptOutputSpeed( struct termios* f_Attribute,
      const void* f_DataPtr ) {
    const ESpeed::TYPE* f_SpeedPtr =
        reinterpret_cast< const ESpeed::TYPE* >( f_DataPtr );
    return TERMIOS_ERROR != cfsetospeed( f_Attribute,
        ptSpeedToPosix( *f_SpeedPtr ) );
  }
//*****************************************************************************
  bool CSerial::ptModemLine( struct termios* f_Attribute,
      const void* f_DataPtr ) {
    const bool* enable = reinterpret_cast< const bool* >( f_DataPtr );
    if( *enable )
      f_Attribute->c_cflag |= CLOCAL;
    else
      f_Attribute->c_cflag &= ~CLOCAL;
    return true;
  }
//*****************************************************************************
  bool CSerial::ptReadMode( struct termios* f_Attribute,
      const void* f_DataPtr ) {
    const bool* enable = reinterpret_cast< const bool* >( f_DataPtr );
    if( *enable )
      f_Attribute->c_cflag |= CREAD;
    else
      f_Attribute->c_cflag &= ~CREAD;

    return true;
  }
//*****************************************************************************
  bool CSerial::ptHardWareFlow( struct termios* f_Attribute,
      const void* f_DataPtr ) {
    const bool* enable = reinterpret_cast< const bool* >( f_DataPtr );
    if( *enable )
      f_Attribute->c_cflag |= CRTSCTS;
    else
      f_Attribute->c_cflag &= ~CRTSCTS;
    return true;
  }
//*****************************************************************************
  bool CSerial::ptSetRawMode( struct termios* f_Attribute,
      const void* f_DataPtr ){
#ifdef __USE_BSD
//    memset( f_Attribute, 0, sizeof( f_Attribute ) );
    cfmakeraw( f_Attribute );
#else
#warning "Not used __USE_BSD. to be tested."
    f_Attribute->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                        | INLCR | IGNCR | ICRNL | IXON);
    f_Attribute->c_oflag &= ~OPOST;
    f_Attribute->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    f_Attribute->c_cflag &= ~(CSIZE | PARENB);
    f_Attribute->c_cflag |= CS8;
#endif
    return true;
  }
//*****************************************************************************
  speed_t CSerial::ptSpeedToPosix( const ESpeed::TYPE& f_Speed ) {
    switch( f_Speed ) {
      case ESpeed::e115200 :
        return B115200;
      case ESpeed::e57600 :
        return B57600;
      case ESpeed::e38400 :
        return B38400;
      case ESpeed::e9600 :
        return B9600;
      case ESpeed::eUnknown :
      default: {
        common::Log()->Out( common::ELogLevel::eWarning, "CTerminal",
            __FUNCTION__, "Unknown type of speed: %d.\n", f_Speed );
        return B0;
      }
    };
  }
//*****************************************************************************
  ESpeed::TYPE CSerial::ptPosixToSpeed( const speed_t& f_Speed ) {
    switch( f_Speed ) {
      case B9600 :
        return ESpeed::e9600;
      case B19200 :
        return ESpeed::e19200;
      case B38400 :
        return ESpeed::e38400;
      case B57600 :
        return ESpeed::e57600;
      case B115200 :
        return ESpeed::e115200;
      case B0 :
      default : {
        common::Log()->Out( common::ELogLevel::eWarning, "CTerminal",
            __FUNCTION__, "Unknown type of speed: %d.\n", f_Speed );
        return ESpeed::eUnknown;
      }
    };
  }
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

}
