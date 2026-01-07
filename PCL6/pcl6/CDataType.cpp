//*****************************************************************************
//        File: CDataType.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include <new>
#include <iostream>

#include "CValueType.hpp"
#include "CData.hpp"
#include "CDataType.hpp"

namespace pcl6 {

  namespace {

    template < int PCLKIND >
    CDataTypePtr CreateType( int f_Type ) {
      static const unsigned char TypeMask = 0x07;
      try {
        switch ( f_Type & TypeMask ) {
          case Value::eUbyte :
            return CDataTypePtr( new CData< PCLKIND, Value::eUbyte >() );
          case Value::eUint16 :
            return CDataTypePtr( new CData< PCLKIND, Value::eUint16 >() );
          case Value::eUint32 :
            return CDataTypePtr( new CData< PCLKIND, Value::eUint32 >() );
          case Value::eInt16 :
            return CDataTypePtr( new CData< PCLKIND, Value::eInt16 >() );
          case Value::eInt32  :
            return CDataTypePtr( new CData< PCLKIND, Value::eInt32 >() );
          case Value::eFloat  :
            return CDataTypePtr( new CData< PCLKIND, Value::eFloat >() );
        default :
          assert( 0 );
          return  CDataTypePtr();
        }
      }
      catch ( std::bad_alloc ){
        PCLErrno = PCLErr::AllocateArray;
        return  CDataTypePtr();
      }
    }

  }; /* namespace */

//******************************************************************************
  CDataType::CDataType( const int& f_Tag ) : CBaseTag( f_Tag ){
  }
//******************************************************************************
  CDataType::~CDataType(){
  }
  //******************************************************************************
  std::size_t CDataType::AsInteger() const{
    return 0;
  }
  //******************************************************************************
  CDataTypePtr CDataType::Create( const Byte& f_DataType ){
    static const unsigned char KindMask = 0xF8;
    switch ( f_DataType & KindMask ) {
      case DataType::eValue :
        return CreateType< DataType::eValue >( f_DataType );
      case DataType::eArray :
        return CreateType< DataType::eArray >( f_DataType );
      case DataType::ePair :
        return CreateType< DataType::ePair >( f_DataType );
      case DataType::eBox :
        return CreateType< DataType::eBox >( f_DataType );
      default :
        return CDataTypePtr();
    }
  }
}
