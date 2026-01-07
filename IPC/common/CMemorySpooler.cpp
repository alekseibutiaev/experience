//*****************************************************************************
//    Project : pu40
//       File : CMemorySpooler.cpp
// Created on : Mar 2, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include "CMemorySpooler.hpp"
#include <iostream>

namespace common {

  namespace Private {

    const unsigned int DEEP_DEFAULT = 512;
    const unsigned int DEEP_MAX = 1024;

//*****************************************************************************
    SMemLog::SMemLog( const ELogLevel::LEVEL& f_Level,
        const std::string& f_Log ) : Level( f_Level ), Log( f_Log ) {
    }
//*****************************************************************************
//*****************************************************************************
    CMemorySpooler::CMemorySpooler( unsigned int f_Deep ) : pvDeep( f_Deep ) {
    }
//*****************************************************************************
    CMemorySpooler::~CMemorySpooler() {
    }
//*****************************************************************************
    void CMemorySpooler::Out( const ELogLevel::LEVEL& f_Level,
        const char* f_Format, va_list f_List ){
#define BUF_MAX 1024
      char buf[ BUF_MAX ];
      buf[ vsnprintf( buf, BUF_MAX - 1, f_Format, f_List ) ] = '\0';
      pvLogBuf.push_back( SMemLog( f_Level, std::string( buf ) ) );
      while( pvLogBuf.size() > pvDeep )
        pvLogBuf.pop_front();
#undef BUF_MAX
    }
//*****************************************************************************
    const ELogSpooler::TYPE CMemorySpooler::Type() const{
      return ELogSpooler::eMemory;
    }
//*****************************************************************************
    void CMemorySpooler::MoveTo( CLogSpooler& f_LogSpooler ){
      // check up itself
      if( this != &f_LogSpooler ) {
        CLogBuf::const_iterator end = pvLogBuf.end();
        for( CLogBuf::const_iterator iter = pvLogBuf.begin(); iter != end;
            ++iter )
          f_LogSpooler.Out( iter->Level, iter->Log.c_str(), 0L );
      }
    }
//*****************************************************************************
    CLogSpooler* CMemorySpooler::Create( const char* f_Param )
        throw( std::bad_alloc ) {
      unsigned int size = atoi( f_Param );
      size = size > DEEP_MAX ? DEEP_MAX : size == 0 ? DEEP_DEFAULT : size;
      return new CMemorySpooler( size );
    }
//*****************************************************************************

  }; /* namespace Private */

};
