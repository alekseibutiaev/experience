//*****************************************************************************
//    Project : pu40
//       File : CFunctionLog.hpp
// Created on : Mar 4, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CFUNCTIONLOG_HPP__
#define __CFUNCTIONLOG_HPP__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "CClassName.hpp"
#include "CLog.hpp"

namespace common {

  class CFunctionLog {
  public:
    template < typename CLASS >
    CFunctionLog( const CLASS* f_Class, const char* f_FuncName ) :
        pvScoopeName( ClassName( f_Class ) ),
        pvFuncName( f_FuncName ) {
      CSinglLog::Instance()->Out( ELogLevel::eDebug, pvScoopeName, pvFuncName,
          "Enter to function.\n" );
    }
    CFunctionLog( const char* f_FileName, const char* f_FuncName ) :
        pvScoopeName( f_FileName ), pvFuncName( f_FuncName ) {
      CSinglLog::Instance()->Out( ELogLevel::eDebug, pvScoopeName, pvFuncName,
          "Enter to function.\n" );
    }
/**/
    ~CFunctionLog() {
      CSinglLog::Instance()->Out( ELogLevel::eDebug, pvScoopeName, pvFuncName,
          "Leave from function.\n" );
    };
  private:
    const char* const pvScoopeName;
    const char* const pvFuncName;
  };

#ifdef USE_FUNCTION_LOGGER
  #define MEMBER_LOG common::CFunctionLog fl_( this, __FUNCTION__ )
  #define STATIC_MEMBER_LOG( Class__ ) common::CFunctionLog fl_( \
    Class__, __FUNCTION__ )
  #define FUNCTION_LOG common::CFunctionLog fl_( __FILE__, __FUNCTION__ )
#else
  #define MEMBER_LOG
  #define STATIC_MEMBER_LOG( Class__ )
  #define FUNCTION_LOG
#endif

}

#endif /* __CFUNCTIONLOG_HPP__ */
