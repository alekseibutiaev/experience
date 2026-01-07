//*****************************************************************************
//    Project : pu40
//       File : CEventObserver.hpp
// Created on : Mar 25, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CEVENTOBSERVER_HPP__
#define __CEVENTOBSERVER_HPP__

#include <vector>
#include <boost/smart_ptr.hpp>

#include "common/common.hpp"

#include "CEvent.hpp"

namespace io {

  namespace EObserver {
    enum RESULT {
      eError = - 1,
      eTimeOut = 0,
      eOk = 1
    };
  }; /* namespace Observer */

  typedef std::vector< CEventPtr > CEventArray;

  class CEventObserver :
    public common::CErrorHandler,
    private common::CClassName< CEventObserver > {
  public:
      enum { eInfinity = -1 };
  public:
    CEventObserver();
    virtual ~CEventObserver();
    bool AddEvent( const CEventPtr& f_Event );
    void DelEvent( const CEventPtr& f_Event );
    EObserver::RESULT WaitEvents( const int& f_Timeout = eInfinity ) const;
  private:
  private:
    CEventArray pvEventArray;
  };

  typedef boost::shared_ptr< CEventObserver > CEventObserverPtr;
  typedef boost::scoped_ptr< CEventObserver > CEventObserverScopedPtr;

}; /* namespace io */

#endif /* __CEVENTOBSERVER_HPP__ */
