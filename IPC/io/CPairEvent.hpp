//*****************************************************************************
//    Project : pu40
//       File : CPairEvent.hpp
// Created on : Apr 15, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CPAIREVENT_HPP__
#define __CPAIREVENT_HPP__

#include "common/common.hpp"
#include "CEvent.hpp"

namespace io {

  class CPairEvent :
      public io::CEvent,
      private common::CClassName< CPairEvent > {
  public:
    CPairEvent();
    virtual ~CPairEvent();
    int& DescriptorWrite();
    const int& DescriptorWrite() const;
    CEvent& WaitEnable( const EAction::TYPE& f_Action );
    CEvent& WaitDisable( const EAction::TYPE& f_Action );
    CEvent& ResetAllWaitings();
    CPairEvent* Clone() const;
    void AddToPollArray( CPollArray& f_PollfdArray ) const;
    void NoticeTarget( const struct pollfd& f_ActiveFlag ) const;
    bool CheckAction( const EAction::TYPE& f_Action ) const;
    bool CheckEvent( const CEvent& f_Event ) const;
    void Print() const;
  private:
    struct pollfd pvPollfdWrite;
  };

  typedef boost::shared_ptr< CPairEvent > CPairEventPtr;
}

#endif /* __CPAIREVENT_HPP__ */
