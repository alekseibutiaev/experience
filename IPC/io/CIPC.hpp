//*****************************************************************************
//    Project : pu40
//       File : CIPC.hpp
// Created on : Sep 29, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CIPC_HPP__
#define __CIPC_HPP__

#include <new>

#include <boost/smart_ptr.hpp>

#include "CDescriptor.hpp"

namespace io {

  class CIPC {
  public:
    virtual ~CIPC(){};
    virtual CDescriptorPtr Server() throw ( std::bad_alloc, std::runtime_error ) = 0;
    virtual CDescriptorPtr Client() throw ( std::bad_alloc, std::runtime_error ) = 0;
  };

  typedef boost::shared_ptr< CIPC > CIPCPtr;

}; /* namespace io */

#endif /* __CIPC_HPP__ */
