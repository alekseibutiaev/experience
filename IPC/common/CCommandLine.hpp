//*****************************************************************************
//    Project : pu40
//       File : CCommandLine.hpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#ifndef __CCOMMANDLINE_HPP__
#define __CCOMMANDLINE_HPP__

#include <getopt.h>
#include <boost/smart_ptr.hpp>

#include "COption.hpp"
#include "CSinglton.hpp"

namespace common {

  namespace EParamRead {
    enum RESULT {
      eUnknown = -1,
      eOk,
      eHelp
    };
  };

  class CCommandLine {
  public:
    EParamRead::RESULT Initialize( const int& f_ArgCount,
        char* const f_ArgValue[], COptionArray& f_OptionArray );
    EParamRead::RESULT Initialize( const int& f_ArgCount,
        char* const f_ArgValue[], ... );
    const char* ProgramName() const;
    const char* PathToProgramm() const;
    const COption* Option( const std::string& f_LongOption ) const;
    const COption* Option( const int& f_ShortOption ) const;
    void ShowHelp() const;
  protected:
    CCommandLine();
    ~CCommandLine();
  private:
    enum { eWithoutShortBegin = 256 };
    enum { eBadOpion = '?' };
    enum { eBadValue = ':' };
  private:
  private:
    COptionArray pvOptionArray;
    std::string pvProgrammName;
    std::string pvPathToProgramm;
    bool pvIsInitialize;
  };

  void BadParameter( const char* const f_Value, const int& f_Short,
      const char* const f_Long );

  typedef CSinglton< CCommandLine > CSinglCommandLine;
  typedef CSingltonPtr< CSinglCommandLine > CSinglCommandLinePtr;

}; /* namespace common */

#endif /* __CCOMMANDLINE_HPP__ */
