//*****************************************************************************
//    Project : pu40
//       File : CSerial.hpp
// Created on : Mar 5, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CSERIAL_HPP__
#define __CSERIAL_HPP__

#include "iocommon.hpp"
#include "CDescriptor.hpp"

#include <termios.h>

#include <stdexcept>

namespace io {

  namespace ESpeed {
    enum TYPE {
      e9600,
      e19200,
      e38400,
      e57600,
      e115200,
      eUnknown
    };
  }; /* namespace ESpeed */

  class CSerial :
    public CDescriptor,
    private common::CClassName< CSerial > {
  public:
    CSerial();
    CSerial( const char* f_Name, const EAccess::MODE& f_Mode,
        bool f_Noctty = true ) throw ( std::runtime_error );
    virtual ~CSerial();
    bool Open( const char* f_Name, const EAccess::MODE& f_Mode,
        bool f_Noctty = true );
    CSerial* Clone() throw( std::bad_alloc );
    bool SetSpeed( const ESpeed::TYPE& f_Speed );
    bool GetSpeed( ESpeed::TYPE& f_Speed ) const;
    bool SetRawMode();
    bool ModemLine( const bool& f_Enable = true );
    bool ReadMode( const bool& f_Enable = true );
    bool HardWareFlow( const bool& f_Enable = true );
  protected:
    typedef bool(ptSigChangeAttribute)( struct termios*, const void* );
    bool ptGetAttribute( struct termios* f_Attribute ) const;
    bool ptChengAttribute( ptSigChangeAttribute f_CangeFunction,
        const void* f_DataPtr = 0L );
    static bool ptInputSpeed( struct termios* f_Attribute,
        const void* f_DataPtr );
    static bool ptOutputSpeed( struct termios* f_Attribute,
        const void* f_DataPtr );
    static bool ptModemLine( struct termios* f_Attribute,
        const void* f_DataPtr );
    static bool ptReadMode( struct termios* f_Attribute,
        const void* f_DataPtr );
    static bool ptHardWareFlow( struct termios* f_Attribute,
        const void* f_DataPtr );
    static bool ptSetRawMode( struct termios* f_Attribute,
        const void* f_DataPtr );
    static speed_t ptSpeedToPosix( const ESpeed::TYPE& f_Speed );
    static ESpeed::TYPE ptPosixToSpeed( const speed_t& f_Speed );
  private:
    struct termios pvTermBackup;
  };

  typedef boost::shared_ptr< CSerial > CSerialPtr;

}; /* namespaca io */

#endif /* __CSERIAL_HPP__ */
