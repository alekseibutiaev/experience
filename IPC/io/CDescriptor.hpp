//*****************************************************************************
//    Project : pu40
//       File : CDescriptor.hpp
// Created on : Mar 4, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CDESCRIPTOR_HPP__
#define __CDESCRIPTOR_HPP__

#include <new>

#include <boost/smart_ptr.hpp>

#include <common/CClassName.hpp>
#include <common/CErrorHandler.hpp>
#include <common/EThreeState.hpp>

#include "CEvent.hpp"

namespace io {

  class CDescriptor :
    public common::CErrorHandler,
    private common::CClassName< CDescriptor > {
  public:
    virtual ~CDescriptor();
    virtual long Write( const void* f_Buf, unsigned long f_Size );
    virtual long Read( void* f_Buf, unsigned long f_Size );
    virtual CDescriptor* Clone() throw( std::bad_alloc ) { return 0; };
    virtual bool NonBlock( bool f_OnOff );
    virtual common::EThreeState::STATE IsNonBlock();
    CEventPtr Event();
    bool& AutoRestart();
    const bool& AutoRestart() const;
  protected:
    CDescriptor();
    CDescriptor( CEvent* f_Event );
    long ptWrite( int& f_Desctiptor, const void* f_Buf, unsigned long f_Size );
    long ptRead( int& f_Desctiptor, void* f_Buf, unsigned long f_Size );
    bool ptNonBlock( int f_Desctiptor, bool f_OnOff );
    common::EThreeState::STATE ptIsNonBlock( int f_Desctiptor );
    int ptGetFlags( int f_Desctiptor );
    bool ptChangeFlag( int f_Descriptor, bool f_OnOff, int f_Flags );
  protected:
    bool ptRestart;
    CEventPtr ptEvent;
  private:
  };

  typedef boost::shared_ptr< CDescriptor > CDescriptorPtr;
  typedef boost::weak_ptr< CDescriptor > CDescriptorWeakPtr;

}; /* namespace io */

#endif /* __CDESCRIPTOR_HPP__ */
