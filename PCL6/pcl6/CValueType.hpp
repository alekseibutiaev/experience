/*
 * CValueType.hpp
 *
 *  Created on: 27.11.2009
 *      Author: alexsy
 */

#ifndef __CVALUETYPE_HPP__
#define __CVALUETYPE_HPP__

#include <cassert>

#include "CTag.hpp"

namespace pcl6 {

//******************************************************************************
//******************************************************************************
  namespace Value {
    enum TYPE{
      eUbyte = 0x00,
      eUint16 = 0x01,
      eUint32 = 0x02,
      eInt16 = 0x03,
      eInt32 = 0x04,
      eFloat = 0x05,
    };
  }
//******************************************************************************
//******************************************************************************
  template < typename DataType >
  static bool SetValue( FileIperator& f_Begin, const FileIperator& f_End,
      DataType& f_Value ) {
    FileIperator::value_type* dataptr =
        reinterpret_cast< FileIperator::value_type* >( &f_Value );
    std::size_t size = sizeof( DataType );
    for( std::size_t index = 0; index < /*sizeof( DataType )*/size; ++index ) {
      if( f_Begin == f_End )
        return false;
      dataptr[ index ] = *f_Begin++;
    }
    return true;
  }
//******************************************************************************
//******************************************************************************
  template < int Value >
  struct CValueType;
//******************************************************************************
  template <>
  struct CValueType< Value::eUbyte > {
    typedef unsigned char value_type;
    enum { ValueType = Value::eUbyte };
  };
//******************************************************************************
  template <>
  struct CValueType< Value::eUint16 > {
    typedef unsigned short value_type;
    enum { ValueType = Value::eUint16 };
  };
//******************************************************************************
  template <>
  struct CValueType< Value::eUint32 > {
    typedef unsigned int value_type;
    enum { ValueType = Value::eUint32 };
  };
//******************************************************************************
  template <>
  struct CValueType< Value::eInt16 > {
    typedef short value_type;
    enum { ValueType = Value::eInt16 };
  };
//******************************************************************************
  template <>
  struct CValueType< Value::eInt32 > {
    typedef int value_type;
    enum { ValueType = Value::eInt32 };
  };
//******************************************************************************
  template <>
  struct CValueType< Value::eFloat > {
    typedef float value_type;
    enum { ValueType = Value::eFloat };
  };

}; /* namespace pcl6 */

#endif /* __CVALUETYPE_HPP__ */
