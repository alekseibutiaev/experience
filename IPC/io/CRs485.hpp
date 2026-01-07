//*****************************************************************************
//    Project : pu40
//       File : CRs485.hpp
// Created on : Jul 13, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CRS485_HPP__
#define __CRS485_HPP__

#include "common/CClassName.hpp"
#include "CSerial.hpp"

namespace io {

  class CRs485 :
    public CSerial,
    private common::CClassName< CRs485 > {
  public:
    CRs485();
    CRs485( const char* f_Name, const EAccess::MODE& f_Mode,
        bool f_Noctty = true ) throw ( std::runtime_error );
    virtual ~CRs485();
    long Write( const void* f_Buf, unsigned long f_Size );
  };

    typedef boost::shared_ptr< CRs485 > CRs485Ptr;

}; /* namespace io */

#endif /* __CRS485_HPP__ */
