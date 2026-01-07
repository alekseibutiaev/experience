//*****************************************************************************
//    Project : pu40
//       File : CLogSpooler.hpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CLOGSPOOLER_HPP__
#define __CLOGSPOOLER_HPP__

#include "ELogSpooler.hpp"
#include "ELogLevel.hpp"

#include <new>
#include <boost/smart_ptr.hpp>
#include <cstdarg>

namespace common {

  class COption;

  namespace Private {

    class CLogSpooler {
    public:
      virtual ~CLogSpooler();
      virtual void Out( const ELogLevel::LEVEL& f_Level, const char* f_Format,
          va_list f_List ) = 0;
      virtual const ELogSpooler::TYPE Type() const = 0;
      static CLogSpooler* Create( const ELogSpooler::TYPE& f_Type,
          const char* f_Param ) throw( std::bad_alloc );
    protected:
      CLogSpooler();
    };

    typedef CLogSpooler* (*FCreateSpooler)( const char* f_Param ) ;

    typedef boost::shared_ptr< CLogSpooler > CLogSpoolerPtr;

  } /* namespace Private */

}; /* namespace common */

#endif /* __CLOGSPOLLER_HPP__ */
