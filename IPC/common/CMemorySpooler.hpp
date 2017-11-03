//*****************************************************************************
//    Project : pu40
//       File : CMemorySpooler.hpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CMEMORYSPOOLER_HPP__
#define __CMEMORYSPOOLER_HPP__

#include "CLogSpooler.hpp"

#include <list>
#include <string>

namespace common {

  namespace Private {

    struct SMemLog{
      SMemLog( const ELogLevel::LEVEL& f_Level, const std::string& f_Log );
      const ELogLevel::LEVEL Level;
      const std::string Log;
    };

    class CMemorySpooler : public CLogSpooler {
    public:
      ~CMemorySpooler();
      void Out( const ELogLevel::LEVEL& f_Level, const char* f_Format,
          va_list f_List );
      const ELogSpooler::TYPE Type() const;
      void MoveTo( CLogSpooler& f_LogSpooler );
      static CLogSpooler* Create( const char* f_Param ) throw( std::bad_alloc );
    private:
      typedef std::list < SMemLog > CLogBuf;
    private:
      CMemorySpooler( unsigned int f_Deep );
    private:
      unsigned int pvDeep;
      CLogBuf pvLogBuf;
    };

  }; /* namespace Private */

}

#endif /* __CMEMORYSPOOLER_HPP__ */
