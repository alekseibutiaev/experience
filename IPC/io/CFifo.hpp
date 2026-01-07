//*****************************************************************************
//    Project : pu40
//       File : CFifo.hpp
// Created on : Sep 29, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CFIFO_HPP__
#define __CFIFO_HPP__

#include <string>
#include <stdexcept>

#include "common/CErrorHandler.hpp"
#include "common/CClassName.hpp"

#include "CIPC.hpp"
#include "iocommon.hpp"

namespace io {

  class CFifoDescriptor;

  const ECreate::MODE DEFAULT_MODE = static_cast< ECreate::MODE >(
      ECreate::eOtherRW | ECreate::eGroupRW | ECreate::eUserRW );

  class CFifo :
      public io::CIPC,
      public common::CErrorHandler,
      private common::CClassName< CFifo > {
  public:
    CFifo( const std::string& f_Name = std::string(),
          ECreate::MODE f_Mode = DEFAULT_MODE )
      throw( std::runtime_error );
    ~CFifo();
    bool Name( const std::string& pvName, ECreate::MODE f_Mode = DEFAULT_MODE );
    CDescriptorPtr Server() throw ( std::bad_alloc, std::runtime_error );
    CDescriptorPtr Client() throw ( std::bad_alloc, std::runtime_error );
  private:
    bool pvCreateNods( const std::string& f_Name, int f_Mode );
  private:
    bool pvIsServer;
    std::string pvWriteName;
    std::string pvReadName;
  };

}; /* namespace io */

#endif /* __CFIFO1_HPP__ */
