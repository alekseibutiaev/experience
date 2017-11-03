//*****************************************************************************
//    Project : pu40
//       File : CSyslogSpooler.hpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CSYSLOGSPOOLER_HPP__
#define __CSYSLOGSPOOLER_HPP__

#include "CLogSpooler.hpp"

namespace common {

  namespace Private {

    class CSyslogSpooler : public CLogSpooler {
    public:
      ~CSyslogSpooler();
      void Out( const ELogLevel::LEVEL& f_Level, const char* f_Format,
          va_list f_List );
      const ELogSpooler::TYPE Type() const;
      static CLogSpooler* Create( const char* f_Param ) throw( std::bad_alloc );
    private:
      CSyslogSpooler( const char* f_ProgramName );
    };

  }; /* namespace Private */

}; /* namespace common */

#endif /* __CSYSLOGSPOOLER_H__ */
