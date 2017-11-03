//*****************************************************************************
//    Project : pu40
//       File : EThreeState.hpp
// Created on : May 4, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __ETHREESTATE_HPP__
#define __ETHREESTATE_HPP__

namespace common {

  namespace EThreeState {
    enum STATE {
      eError = -1,
      eReset,
      eSet
    };
  };

}; /* namespace common */

#endif /* __ETHREESTATE_HPP__ */
