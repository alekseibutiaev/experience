//*****************************************************************************
//    Project : pu40
//       File : CConsoleSpooler.hpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CCONSOLESPOOLER_HPP__
#define __CCONSOLESPOOLER_HPP__

#include "CLogSpooler.hpp"

namespace common {

  namespace Private {

    class CConsoleSpooler : public CLogSpooler {
    public:
      ~CConsoleSpooler();
      void Out( const ELogLevel::LEVEL& f_Level, const char* f_Format,
          va_list f_List );
      const ELogSpooler::TYPE Type() const;
      static CLogSpooler* Create( const char* f_Param ) throw( std::bad_alloc );
    private:
      CConsoleSpooler();
    };

  }; /* namespace Private */

}; /* namespace common */

#endif /* __CCONSOLESPOOLER_H__ */
