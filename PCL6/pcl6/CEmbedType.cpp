//*****************************************************************************
//        File: CEmbedType.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//******************************************************************************

#include <new>
#include <iostream>

#include "CEmbedType.hpp"
#include "CEmbedData.hpp"

namespace pcl6 {
//******************************************************************************
  CEmbedType::CEmbedType( const Byte& f_Tag ) : COperator( f_Tag ) {
    OPERATOR_NAME;
  };
//******************************************************************************
  CEmbedType::~CEmbedType() {
  }
//******************************************************************************
  CEmbedTypePtr CEmbedType::Create( const Byte& f_Tag ){
    try{
      switch( f_Tag ){
        case EmbedData::eDataLength:
          return CEmbedTypePtr( new CEmbedData< EmbedData::eDataLength >() );
        case EmbedData::eDataLengthByte:
          return CEmbedTypePtr( new CEmbedData< EmbedData::eDataLengthByte >() );
        default:
          return CEmbedTypePtr();
      }
    }
    catch( std::bad_alloc ) {
      return CEmbedTypePtr();
    }
  }
} /* namespace pcl6 */

#if 0
//******************************************************************************
  CEmbedData::CEmbedData( const int& f_Tag ) : COperator( f_Tag ), pvSize( 0 ){
    OPERATOR_NAME;
  }
//******************************************************************************
  CEmbedData::~CEmbedData() {
  }
//******************************************************************************
  bool CEmbedData::IsValid() const{
    return pvSize;
  }
//******************************************************************************
  bool CEmbedData::SetAttributes(
      const CAttributeArray& f_Atributes ){
    return false;
  }
//******************************************************************************
  bool CEmbedData::SetString( FileIperator& f_Begin,
      const FileIperator& f_End ){
    return false;
  }
//******************************************************************************
  bool CEmbedData::SetArray( FileIperator& f_Begin, const FileIperator& f_End,
      const std::size_t& f_Lenght ) {
    try {
      int a = 0;
      char* b = (char*)&a;
      *b = *f_Begin;
      std::size_t lenght = f_Lenght + ( Tag() == 0xfa ? sizeof( int ) :
        sizeof( char ) );
      pvArray = CArray( new Byte[ lenght ] );
      pvSize = 0;
      while( f_Begin != f_End && pvSize < lenght )
        pvArray[ pvSize++ ] = *f_Begin++;
      return f_Begin != f_End && pvSize == lenght;
      b = 0;
    }
    catch( std::bad_alloc& ) {
      std::cerr << "Can not allocated array." << std::endl;
      return false;
    }
  }
//******************************************************************************
  const std::size_t& CEmbedData::Size() const{
    return pvSize;
  }
#endif
