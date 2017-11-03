//*****************************************************************************
//    Project : pu40
//       File : CClassName.hpp
// Created on : Mar 3, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@kiskom.ru
//*****************************************************************************

#include <cassert>
#include <cstdio>
#include <iostream>

#include "chartype.h"
#include "COption.hpp"

namespace common {

  const int BUF_SIZE = 1024;
  const char* DELEMITER = "  ";
  const char* DEFAULTSTR = "Default: ";

  const char* COption::BOOLEAN_TRUE = "true";
  const char* COption::BOOLEAN_FALSE = "false";
  const char* BOOLEAN_1 = "1";
  const char* BOOLEAN_0 = "0";

//*****************************************************************************
  COption::COption( const std::string& f_LongOption, const int& f_ShortOption,
        const EArgument::FLAG& f_ArgFlag, const std::string& f_DefaultValue,
        const std::string& f_Description ) : pvLongOption( f_LongOption ),
      pvShortOption( f_ShortOption ), pvArgFlag( f_ArgFlag ),
      pvDefaultValue( f_DefaultValue ), pvDescription( f_Description ),
      pvValue( f_DefaultValue ) {
    if( pvArgFlag == EArgument::eWithoutArg ||
        pvArgFlag == EArgument::eOptionalArg ) {
      assert( pvValue == BOOLEAN_TRUE ||
          pvValue == BOOLEAN_1 || pvValue == BOOLEAN_FALSE || pvValue == BOOLEAN_0 ||
          ( pvLongOption == std::string() && 0 == f_ShortOption &&
            f_ArgFlag == EArgument::eWithoutArg, pvDefaultValue == std::string(),
            pvValue == std::string() ) );
#if 0
      bool Not_correct_value_by_default = pvValue == BOOLEAN_TRUE ||
        pvValue == BOOLEAN_1 || pvValue == BOOLEAN_FALSE || pvValue == BOOLEAN_0 ||
        ( pvLongOption == std::string() && 0 == f_ShortOption &&
          f_ArgFlag == EArgument::eWithoutArg, pvDefaultValue == std::string(),
          pvValue == std::string() );
      assert( Not_correct_value_by_default );
#endif
    }
  }
//*****************************************************************************
  COption::~COption() {
  }
//*****************************************************************************
  void COption::Update( const char* f_OptArg ) {
    switch( pvArgFlag ) {
      case EArgument::eRequiredArg :
        assert( 0L != f_OptArg );
      case EArgument::eOptionalArg :
        if( 0L != f_OptArg ) {
          pvValue = f_OptArg;
          break;
        }
      case EArgument::eWithoutArg :
        pvSetBoolean();
        break;
    }
  }
//*****************************************************************************
  int& COption::ShortOption() {
    return pvShortOption;
  }
//*****************************************************************************
  const int& COption::ShortOption() const {
    return pvShortOption;
  }
//*****************************************************************************
  const std::string& COption::LongOption() const {
    return pvLongOption;
  }
//*****************************************************************************
  const char* COption::Short() const {
    std::size_t endIndex = 0;
    if( 0 != wisalpha( pvShortOption ) || 0 != wisdigit( pvShortOption ) ) {
      pvBuf[ 0 ] = static_cast< char >( pvShortOption );
      pvBuf[ 1 ] = ':';
      pvBuf[ 2 ] = ':';
      switch( pvArgFlag ){
        case EArgument::eOptionalArg:
          ++endIndex;
        case EArgument::eRequiredArg:
          ++endIndex;
        default:
          ++endIndex;
      }
    }
    pvBuf[ endIndex ] = '\0';
    return pvBuf;
  }
#if 0
//*****************************************************************************
  void COption::Help() const {
    // print short option
    if( 0 != wisalpha( pvShortOption ) )
      std::cout << '-' << static_cast< char >( pvShortOption ) << DELEMITER;
    else
      std::cout << "  " << DELEMITER;
    // print long option
    if( !pvLongOption.empty() )
      std::cout << "--" << pvLongOption << DELEMITER;
    else
      std::cout << "            " << DELEMITER;
    // print description option
    if( !pvDescription.empty() )
      std::cout << pvDescription << DELEMITER;
    else
      std::cout << "" << DELEMITER;
    // print default
    if( !pvDefaultValue.empty() )
      std::cout << DEFAULTSTR << pvDefaultValue;
    std::cout << std::endl << std::endl;
  }
#endif
//*****************************************************************************
  bool COption::GetValue( bool& f_Value, std::string* f_Parameter ) const {
    if( pvValue == BOOLEAN_FALSE || pvValue == BOOLEAN_0 )
      f_Value = false;
    else if( pvValue == BOOLEAN_TRUE || pvValue == BOOLEAN_1 )
      f_Value = true;
    // get optional of option.
    else if( pvArgFlag == EArgument::eOptionalArg && 0L != f_Parameter ) {
      f_Value = true;
      *f_Parameter = pvValue;
      return false;
    }
    else
      assert( false );
    return true;
  }
//*****************************************************************************
  void COption::GetValue( std::string& f_Value ) const {
    f_Value = pvValue;
  }
//*****************************************************************************
  struct option COption::GnuOption() const {
    int flag = pvArgFlag == EArgument::eRequiredArg ? required_argument :
      pvArgFlag == EArgument::eOptionalArg ? optional_argument : no_argument;
    option result = { pvLongOption.empty() ? 0 : pvLongOption.c_str(),
        flag, 0, pvShortOption };
    return result;
  }
//*****************************************************************************
  SOptionData COption::Help() const {
    SOptionData result;
    result.Short = pvShortOption;
    result.Long = pvLongOption;
    result.Description = pvDescription;
    result.DefaultValue = pvDefaultValue;
    return result;
  }
//*****************************************************************************
  void COption::pvSetBoolean() {
    if( pvValue == BOOLEAN_TRUE || pvValue == BOOLEAN_1 )
      pvValue = BOOLEAN_FALSE;
    else if( pvValue == BOOLEAN_FALSE || pvValue == BOOLEAN_0 )
      pvValue = BOOLEAN_TRUE;
    else
      assert( false );
  }
//*****************************************************************************

}; /* namespace common */
