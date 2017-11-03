//*****************************************************************************
//    Project : pu40
//       File : EAction.hpp
// Created on : Dec 12, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef _EACTION_HPP__
#define _EACTION_HPP__


namespace io{

  namespace EAction {
    enum TYPE {
      eReadNornal,
      eReadPriority,
      eWriteNormal,
      eErrorCondition,
      eErrorHungUp,
      eErrorRequest
    };
  }; /* namespace EAction */

  const unsigned short& ToPosix( const EAction::TYPE& f_Action );

};

#endif /* _EACTION_HPP__ */
