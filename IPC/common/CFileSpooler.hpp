//*****************************************************************************
//    Project : pu40
//       File : CFileSpooler.hpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CFILESPOOLER_HPP__
#define __CFILESPOOLER_HPP__

#include "CLogSpooler.hpp"

namespace common {

  namespace Private {

    class CFileSpooler : public CLogSpooler {
    public:
      ~CFileSpooler();
      void Out( const ELogLevel::LEVEL& f_Level, const char* f_Format,
        va_list f_VarList );
      const ELogSpooler::TYPE Type() const;
      static CLogSpooler* Create( const char* f_Param ) throw( std::bad_alloc );
    private:
      CFileSpooler( const char* f_Param );
    private:
      FILE* pvOut;
    };

  }; /* namespace Private */

}

#endif /* __CFILESPOOLER_HPP__ */
