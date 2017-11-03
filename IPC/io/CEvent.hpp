//*****************************************************************************
//    Project : pu40
//       File : CEvent.hpp
// Created on : Mar 24, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CEVENT_HPP__
#define __CEVENT_HPP__

#include <poll.h>

#include <vector>
#include <boost/smart_ptr.hpp>

#include <common/CClassName.hpp>

#include "CEventTarget.hpp"
#include "EAction.hpp"


namespace io {

  typedef std::vector< pollfd > CPollArray;

  class CEvent :
      private common::CClassName< CEvent > {
  public:
    CEvent();
    CEvent( const struct pollfd& f_Pollfd );
    virtual ~CEvent();
    int& Descriptor();
    const int& Descriptor() const;
    void Target( CEventTargetPtr f_Target );
    virtual CEvent& WaitEnable( const EAction::TYPE& f_Action );
    virtual CEvent& WaitDisable( const EAction::TYPE& f_Action );
    virtual CEvent& ResetAllWaitings();
    virtual CEvent* Clone() const;
    virtual void AddToPollArray( CPollArray& f_PollArray ) const;
    virtual void NoticeTarget( const struct pollfd& f_ActiveFlag ) const;
    virtual bool CheckAction( const EAction::TYPE& f_Action ) const;
    virtual bool CheckEvent( const CEvent& f_Event ) const;
    virtual void Print() const;
  protected:
    void ptAddToPollArray( CPollArray& f_PollfdArray,
        const struct pollfd& f_Polfd ) const;
    void ptNoticeTarget( const struct pollfd& f_ActiveFlag ) const;
  protected:
  private:
    CEventTargetWeakPtr pvTargetPtr;
    struct pollfd pvPollfd;
  };

  typedef boost::shared_ptr< CEvent > CEventPtr;
  typedef boost::scoped_ptr< CEvent > CEventScopedPtr;

  inline bool CompareDescriptor( const pollfd& f_Left, const pollfd& f_Right );

}; /* namespace io */

#endif /* __CEVENT_HPP__ */
