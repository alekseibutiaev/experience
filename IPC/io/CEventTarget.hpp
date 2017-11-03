//*****************************************************************************
//    Project : pu40
//       File : CEventTarget.hpp
// Created on : Mar 25, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CEVENTTARGET_HPP__
#define __CEVENTTARGET_HPP__

#include <vector>
#include <iostream>

#include <boost/smart_ptr.hpp>

#include "common/CClassName.hpp"

namespace io {

  class CEvent;

  namespace EOrder {
    enum MODE {
      eNext,
      eStop
    };
  }; /* namespace EOrder */

  //Sequence of calls

  class CEventTarget :
      private common::CClassName< CEventTarget > {
  public:
    virtual ~CEventTarget();
    // method return EOrder::eNext for check up next flags.
    // order call ErrorRequest ErrorHungUp ErrorCondition WriteNormal
    // ReadPriority ReadNormal
    virtual EOrder::MODE ReadNormal( const CEvent& f_Action );
    virtual EOrder::MODE ReadPriority( const CEvent& f_Action );
    virtual EOrder::MODE WriteNormal( const CEvent& f_Action );
    virtual EOrder::MODE ErrorCondition( const CEvent& f_Action );
    virtual EOrder::MODE ErrorHungUp( const CEvent& f_Action );
    virtual EOrder::MODE ErrorRequest( const CEvent& f_Action );
    virtual void Notice( const CEvent& f_Action );
  protected:
    CEventTarget();
  };

  typedef boost::shared_ptr< CEventTarget > CEventTargetPtr;
  typedef boost::weak_ptr< CEventTarget > CEventTargetWeakPtr;

}; /* namespace io */

#endif /* __CEVENTTARGET_HPP__ */
