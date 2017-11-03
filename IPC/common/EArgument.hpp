//*****************************************************************************
//    Project : pu40
//       File : EArgument.hpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __EARGUMENT_HPP__
#define __EARGUMENT_HPP__

namespace common{

  namespace EArgument{
    enum FLAG{
      eWithoutArg   = 0,
      eRequiredArg  = 1,
      eOptionalArg  = 2,
    };
  };

}; /* namespace common */

#endif /* __EARGUMENT_HPP__ */
