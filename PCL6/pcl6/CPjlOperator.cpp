//*****************************************************************************
//        File: CPjlOperator.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include <iostream>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <new>

#include "CPjlOperator.hpp"

namespace pcl6 {

  namespace {

    class CStringCollect {
    public:
      CStringCollect( std::string& f_Result ) : pvResult( f_Result ) {}
      bool operator()( const Byte& f_Byte ) {
        pvResult.push_back( f_Byte );
        return f_Byte == 0x0a;
      }
    private:
      std::string& pvResult;
    };

    class CPjlFilter{
    public:
      bool operator()( const int& f_Symbol ) const {
        return isspace( f_Symbol ) || f_Symbol == '=';
      }
    };

    void parsePjlCommand( const std::string& f_PjlString,
        std::string& f_Command, std::string& f_Parameter,
        std::string& pvValue ){
      typedef std::vector< std::string > CStringArray;
      CStringArray stringsArray;
      std::string::const_iterator begin = f_PjlString.begin();
      std::string::const_iterator end = f_PjlString.end();
      for(;;) {
        std::string::const_iterator temp;
        if( ( temp  = std::find_if( begin, end, CPjlFilter() ) ) == end )
          break;
        if( begin != temp )
          stringsArray.push_back( std::string( begin, temp ) );
        if( *temp == '=' )
          stringsArray.push_back( std::string( "=" ) );
        begin = temp;
        ++begin;
      }
      f_Command = stringsArray[ 1 ];
      // find equal operator
      CStringArray::iterator arrayEnd = stringsArray.end();
      CStringArray::iterator iter = std::find( stringsArray.begin(),
          arrayEnd, std::string( "=" ) );
      std::size_t valueindex = 2;
      if( iter != arrayEnd ) {
        f_Parameter = stringsArray[ 2 ];
        valueindex = 4;
      }
      for( ; valueindex < stringsArray.size(); ++valueindex )
        pvValue += stringsArray[ valueindex ] + ' ';
      pvValue.erase( --pvValue.end() );
#if 0
      std::cout << "Comand: " << f_Command << " Parameter: " << f_Parameter <<
        " Value: " << pvValue << std::endl;
#endif
    }

  }; /* namespace */

//******************************************************************************
  CPjlOperator::CPjlOperator( const Byte& f_OperatorTag ) :
      COperator( f_OperatorTag ), pvHaveBeenParsed( false ) {
    OPERATOR_NAME;
  }
//******************************************************************************
  CPjlOperator::~CPjlOperator(){
  }
//******************************************************************************
  CPjlOperatorPtr CPjlOperator::Create( const Byte& f_Tag ) {
    try {
      switch ( f_Tag ) {
        // PJL Operators
        case PjlTag::eStreamHeader :
        case PjlTag::eHeader :
        case PjlTag::ePJL :
          return CPjlOperatorPtr( new CPjlOperator( f_Tag ) );
        default :
          return CPjlOperatorPtr();
      }
    }
    catch( std::bad_alloc ){
      return CPjlOperatorPtr();
    }

  }
//******************************************************************************
  bool CPjlOperator::SetString( FileIperator& f_Begin,
      const FileIperator& f_End ) {
    f_Begin = std::find_if( f_Begin, f_End, CStringCollect( pvPjlString ) );
    ++f_Begin;
    return IsValid();
  }
//******************************************************************************
  bool CPjlOperator::IsValid() const {
    return !pvPjlString.empty();
  }
//******************************************************************************
  std::string CPjlOperator::Command() const{
    if( Tag() != PjlTag::ePJL )
      return std::string();
    if( !pvHaveBeenParsed ){
      parsePjlCommand( pvPjlString, pvCommand, pvParameter, pvValue );
      pvHaveBeenParsed = true;
      }
    return pvCommand;
  }
//******************************************************************************
  std::string CPjlOperator::Parameter() const{
    if( Tag() != PjlTag::ePJL )
      return std::string();
    if( !pvHaveBeenParsed ){
      parsePjlCommand( pvPjlString, pvCommand, pvParameter, pvValue );
      pvHaveBeenParsed = true;
    }
    return pvParameter;
  }
//******************************************************************************
  std::string CPjlOperator::Value() const{
    if( Tag() != PjlTag::ePJL )
      return std::string();
    if( !pvHaveBeenParsed ){
      parsePjlCommand( pvPjlString, pvCommand, pvParameter, pvValue );
      pvHaveBeenParsed = true;
    }
    return pvValue;
  }

}; /* namespace pcl6 */
