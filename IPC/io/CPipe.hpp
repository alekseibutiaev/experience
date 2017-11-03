//*****************************************************************************
//    Project : pu40
//       File : CPipe.hpp
// Created on : Sep 29, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CPIPE_HPP__
#define __CPIPE_HPP__

#include <sys/types.h>

#include <stdexcept>

#include <common/CErrorHandler.hpp>
#include <common/CClassName.hpp>

#include "CIPC.hpp"

namespace io {

  class CPipe :
      public io::CIPC,
      public common::CErrorHandler,
      private common::CClassName< CPipe > {
  public:
    CPipe() throw( std::runtime_error );
    ~CPipe();
    CDescriptorPtr Server() throw ( std::bad_alloc );
    CDescriptorPtr Client() throw ( std::bad_alloc );
  private:
    enum DIRECTION {
      eRead,
      eWrite,
      eCount
    };
  private:
    pid_t pvParentProcess;
    int pvPipeA[ eCount ];
    int pvPipeB[ eCount ];
  };

}; /* class CPipe */

#endif /* __CPIPE1_HPP__ */
