//*****************************************************************************
//    Project : pu40
//       File : CFifoDescriptor.hpp
// Created on : Nov 25, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru 
//*****************************************************************************

#ifndef __CFIFODESCRIPTOR_HPP__
#define __CFIFODESCRIPTOR_HPP__

#include <string>

#include "CPairDescriptor.hpp"
#include "common/CClassName.hpp"

namespace io {

  class CFifoDescriptor :
      public CPairDescriptor,
      private common::CClassName< CFifoDescriptor > {
    friend CFifoDescriptor* FifoServer( const std::string& f_WriteName,
        const std::string& f_ReadName, int& f_Errno )
          throw( std::bad_alloc, std::runtime_error );
    friend CFifoDescriptor* FifoClient( const std::string& f_WriteName,
        const std::string& f_ReadName, int& f_Errno )
          throw( std::bad_alloc, std::runtime_error );
  public:
    virtual ~CFifoDescriptor();
    long Write( const void* f_Buf, unsigned long f_Size );
  private:
    // Client constructor
    CFifoDescriptor( int f_Read, int f_Write );
    // Server constructor
    CFifoDescriptor( int f_Read, const std::string& f_WriteName );
  private:
    std::string pvName;
  };

}

#endif /* __CFIFODESCRIPTOR_HPP__ */
