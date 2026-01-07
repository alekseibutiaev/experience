//*****************************************************************************
//    Project : pu40
//       File : CClassName.hpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CCLASSNAME_HPP__
#define __CCLASSNAME_HPP__

#include "CLog.hpp"

namespace common {

  template < typename CLASS >
  struct TypeToType {
    typedef CLASS orig_type;
  };

  template < typename CLASS >
  class CClassName {
  public:
    typedef CClassName< CLASS > class_type;
    template< typename SELF >
    friend const char* ClassName( const SELF* );
  protected:
    CClassName( const char* f_ClassName ) {
      pvClassName = f_ClassName;
    }
    virtual ~CClassName(){};
  private:
    static const char* pvClassName;
  };

  template< typename CLASS >
  const char* CClassName< CLASS >::pvClassName = 0L;

  template< typename SELF >
  inline const char* ClassName( const SELF* ) {
    return CClassName< SELF >::pvClassName;
  }

}; /* namespace common */

#endif /* __CCLASSNAME_HPP__ */
