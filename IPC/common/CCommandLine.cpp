//*****************************************************************************
//    Project : pu40
//       File : CCommandLine.cpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include <cstdarg>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <iterator>
#include <boost/shared_ptr.hpp>

#include "chartype.h"
#include "CCommandLine.hpp"
#include "CVaList.hpp"

namespace common {

  namespace {

//*****************************************************************************
    const std::string HELP_LONG = "help";
    const int HELP_SHORT = 'h';
    const EArgument::FLAG HELP_FLAG = EArgument::eWithoutArg;
    const std::string HELP_DEFAULT = COption::BOOLEAN_FALSE;
    const std::string HELP_DESCRIPTOR = "Give this help.";

    static COption HELP_OPTIONS(
        HELP_LONG,
        HELP_SHORT,
        HELP_FLAG,
        HELP_DEFAULT,
        HELP_DESCRIPTOR );

    static COption dummyOption;

//*****************************************************************************
    class CFindByShort {
    public:
      CFindByShort( const int& f_Opton ) : pvOpton( f_Opton ) {}
      bool operator()( const COption* f_Option ) const {
        return f_Option->ShortOption() == pvOpton;
      }
    protected:
      int pvOpton;
    };
//*****************************************************************************
    class CFindByLong {
    public:
      CFindByLong( const std::string& f_Opton ) : pvOpton( f_Opton ) {}
      bool operator()( const COption* f_Option ) const {
        return f_Option->LongOption() == pvOpton;
      }
    protected:
      std::string pvOpton;
    };
//*****************************************************************************
    class CCorrectShortOption {
    public:
      CCorrectShortOption( const int& f_ShortBegin ) :
        pvShortBegin( f_ShortBegin ) {
      }
      COption* operator()( COption* f_Option ) {
        if( f_Option->ShortOption() >= COption::eWithoutShort )
          f_Option->ShortOption() = pvShortBegin++;
        return f_Option;
      }
    private:
      int pvShortBegin;
    };

    class CShowOption : public SOptionData {
    public:
      enum { eDefaultConsole = 80 };
    public:
      CShowOption( const unsigned int& f_MaxConsoleLenght = eDefaultConsole ) {
        pvMaxConsoleLenght = f_MaxConsoleLenght;
      }
      CShowOption( const SOptionData& f_OptionData ) :
          SOptionData( f_OptionData ) {
        pvMaxLongLenght = std::max( pvMaxLongLenght,
            f_OptionData.Long.size() +
            static_cast< typeof( pvMaxLongLenght ) >( ePrefixForLongOptionSize ) );
      }
      void Show() {
        if( 0 == Short && Long.empty() )
          return;
        // Show short option
        if( 0 != wisalpha( Short ) )
          std::cout << '-' << static_cast< char >( Short ) << ' ';
        else
          std::cout << "   ";
        //Show long option
        std::cout << std::setw( pvMaxLongLenght ) << std::setfill( ' ' ) <<
            ( "--" + Long) << ' ';
        std::string tabString( eShortLenght + pvMaxLongLenght + 1, ' ' );
        std::size_t begin = 0;
        std::size_t current = 0;
        while( current < Description.size() ) {
          std::string line;
          if( Description.size() < pvMaxConsoleLenght - tabString.size() ) {
            line = Description;
            current = std::string::npos;
          }
          else {
            // To be displaced for the greatest possible length of a line.
            current += begin + pvMaxConsoleLenght - tabString.size();
            // To find the last delimiter character.
            current = Description.find_last_of( pvDelimitreCharacter,
                std::min( current, Description.size() ) ) + 1;
            // To take a piece of a line.
            line = std::string( Description, begin, current );
           begin = current;
          }
          std::cout << line << std::endl << tabString;
        }
        std::cout << "Default: " << DefaultValue << std::endl << std::endl;
      }
    private:
      enum { eShortLenght = 3 };
      enum { ePrefixForLongOptionSize = 2 };
    private:
      static unsigned int pvMaxConsoleLenght;
      static unsigned long pvMaxLongLenght;
      static const std::string pvDelimitreCharacter;
    };

    unsigned int CShowOption::pvMaxConsoleLenght = CShowOption::eDefaultConsole;
    unsigned long CShowOption::pvMaxLongLenght = 0;
    const std::string CShowOption::pvDelimitreCharacter = " \f\r\n\v\t.,";

  }; /* namespace */

//*****************************************************************************
  void BadParameter( const char* const f_Value, const int& f_Short,
      const char* const f_Long ) {
    fprintf( stderr, "\n\nThe parameter %s for option %c, %s is not valid.\n\n",
        f_Value, wisalpha( f_Short ) ? f_Short : ' ', f_Long );
  }
//*****************************************************************************
  CCommandLine::CCommandLine() : pvIsInitialize( false ) {
  }
//*****************************************************************************
  CCommandLine::~CCommandLine() {
  }
//*****************************************************************************
  EParamRead::RESULT CCommandLine::Initialize( const int& f_ArgCount,
      char* const f_ArgValue[], COptionArray& f_OptionArray ) {
    // push help option.
    pvOptionArray.push_back( &HELP_OPTIONS );
    // copy and correct short option.
    std::transform( f_OptionArray.begin(), f_OptionArray.end(),
        std::back_inserter( pvOptionArray ),
        CCorrectShortOption( 256 ) );
    // push end option.
    pvOptionArray.push_back( &dummyOption );
    // build long optional array.
    std::vector< option > longOption;
    std::transform( pvOptionArray.begin(), pvOptionArray.end(),
        std::back_inserter( longOption ), std::mem_fun( &COption::GnuOption ) );
    // build short optional string.
    std::string shortOptionList;
    for( COptionArray::iterator iter = pvOptionArray.begin();
        iter != pvOptionArray.end(); ++iter )
      shortOptionList += std::string( (*iter)->Short() );
    // set option
    int shortOption;
    int optionIndex;
    while( ( shortOption = getopt_long( f_ArgCount, f_ArgValue,
        shortOptionList.c_str(), &longOption[ 0 ], &optionIndex ) ) > -1 ) {
      if( eBadOpion == shortOption || eBadValue == shortOption ) {
        ShowHelp();
        return common::EParamRead::eUnknown;
      }
      else if( shortOption == HELP_OPTIONS.ShortOption() ) {
        ShowHelp();
        return common::EParamRead::eHelp;
      }
      else {
        COptionArray::iterator opt;
        COptionArray::iterator end = pvOptionArray.end();
        if( ( opt = std::find_if( pvOptionArray.begin(), end,
            CFindByShort( shortOption ) ) ) != end )
          (*opt)->Update( optarg );
      }
    }
    // get name and path of program
    std::string fullname( f_ArgValue[ 0 ] );
    std::size_t found = fullname.find_last_of( "/\\" );
    pvProgrammName = fullname.substr( found + 1 );
    pvPathToProgramm = fullname.substr( 0, found );
    pvIsInitialize = true;
    return common::EParamRead::eOk;
  }
//*****************************************************************************
  EParamRead::RESULT CCommandLine::Initialize( const int& f_ArgCount,
      char* const f_ArgValue[], ... ) {
    COptionArray optionarray;
    COption* opionPtr;
    CVaList va;
    va_start( va.GetList(), f_ArgValue );
    while( 0L != ( opionPtr = va.NextArg( opionPtr ) ) )
      optionarray.push_back( opionPtr );
    return Initialize( f_ArgCount, f_ArgValue, optionarray );
  }
//*****************************************************************************
  const char* CCommandLine::ProgramName() const {
    assert( pvIsInitialize );
    return pvProgrammName.c_str();
  }
//*****************************************************************************
  const char* CCommandLine::PathToProgramm() const {
    assert( pvIsInitialize );
    return pvPathToProgramm.c_str();
  }
//*****************************************************************************
  const COption* CCommandLine::Option( const std::string& f_LongOption ) const {
    assert( pvIsInitialize );
    COptionArray::const_iterator opt;
    COptionArray::const_iterator end = pvOptionArray.end();
    if( ( opt = std::find_if( pvOptionArray.begin(), end,
        CFindByLong( f_LongOption ) ) ) != end ) {
      return *opt;
    }
    fprintf( stderr, "%s. Option: %s not declared.\n",  __PRETTY_FUNCTION__,
        f_LongOption.c_str() );
    assert( false );
    return 0L;
  }
//*****************************************************************************
  const COption* CCommandLine::Option( const int& f_ShortOption ) const {
    assert( pvIsInitialize );
    COptionArray::const_iterator opt;
    COptionArray::const_iterator end = pvOptionArray.end();
    if( ( opt = std::find_if( pvOptionArray.begin(), end,
        CFindByShort( f_ShortOption ) ) ) != end ) {
      return *opt;
    }
    fprintf( stderr, "%s. Option: %c or %d not declared.\n",  __PRETTY_FUNCTION__,
        wisalpha( f_ShortOption ) ? wisalpha( f_ShortOption ) : ' ',
        f_ShortOption );
    assert( false );
    return 0L;
  }
//*****************************************************************************
  void CCommandLine::ShowHelp() const {
    CShowOption();
    std::vector< CShowOption > ShowOption;
    std::transform( pvOptionArray.begin(), pvOptionArray.end(),
        std::back_inserter( ShowOption ), std::mem_fun( &COption::Help ) );
    std::for_each( ShowOption.begin(), ShowOption.end(),
        std::mem_fun_ref( &CShowOption::Show ) );
  }
//*****************************************************************************

}; /* namespace common */
