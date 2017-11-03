//*****************************************************************************
//    Project : pu40
//       File : CThreadAdapter.hpp
// Created on : Apr 13, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __CTHREADADAPTER_HPP__
#define __CTHREADADAPTER_HPP__

namespace common {

  template< typename FUNC, typename PARAM >
  class CThreadAdapter {
  public:
    CThreadAdapter( FUNC& f_Func, PARAM& f_Param ) :
        pvFunc( f_Func ), pvParam( f_Param ){
    }
    void operator()() {
      pvFunc( pvParam );
    }
  private:
    FUNC pvFunc;
    PARAM& pvParam;
  };

}

#endif /* __CTHREADADAPTER_HPP__ */
