//*****************************************************************************
//        File: CData.hpp
//     Project: kopirkin
//  Created on: 26.11.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CDATA_HPP__
#define __CDATA_HPP__

#include <new>
#include <utility>
#include <iostream>
#include <algorithm>

#include <boost/smart_ptr.hpp>

#include "ParserErrno.hpp"
#include "CDataType.hpp"
#include "CValueType.hpp"

namespace pcl6 {

  namespace DataType {
    enum TYPE {
      eValue = 0xC0,
      eArray = 0xC8,
      ePair = 0xD0,
      eBox = 0xE0,
    };
  }; /* namespace DataType */

  namespace {
    template < typename TYPE >
    class CFillArray {
    public:
      CFillArray( FileIperator& f_Begin, const FileIperator& f_End ) :
        pvBegin( f_Begin ), pvEnd( f_End ) {
      }
      TYPE operator()(){
        TYPE temp;
        SetValue( pvBegin, pvEnd, temp );
        return temp;
      }
    private:
      FileIperator& pvBegin;
      const FileIperator& pvEnd;
    };
  }/* namespace */


//******************************************************************************
  template < int PCLKIND, int PCLTYPE >
  class CData;
//******************************************************************************
  typedef CData< DataType::eValue, Value::eUbyte > CValueUByte;
  typedef CData< DataType::eValue, Value::eUint16 > CValueUShort;
//******************************************************************************
  template < int PCLTYPE >
  class CData < DataType::eValue, PCLTYPE > : public CDataType {
  public:
    typedef typename CValueType< PCLTYPE >::value_type value_type;
    CData() : CDataType( Tag ), pvValue( 0 ) {

    };
    ~CData() {};
    value_type& Value() {
      return pvValue;
    }
    const value_type& Value() const {
      return pvValue;
    }
  bool SetData( FileIperator& f_Begin, const FileIperator& f_End ) {
    return SetValue( f_Begin, f_End, pvValue );
  }
  std::size_t AsInteger() const {
    return static_cast< std::size_t >( pvValue );
  }
  private:
    value_type pvValue;
    enum { Tag = DataType::eValue | CValueType< PCLTYPE >::ValueType };
  };
//******************************************************************************
  template < int PCLTYPE >
  class CData < DataType::ePair, PCLTYPE > : public CDataType {
  public:
    typedef typename CValueType< PCLTYPE >::value_type value_type;
    CData() : CDataType( Tag ), pvValueX( 0 ), pvValueY( 0 ) {};
    ~CData() {};
    value_type& ValueX() {
      return pvValueX;
    }
    const value_type& ValueX() const {
      return pvValueX;
    }
    value_type& ValueY() {
      return pvValueY;
    }
    const value_type& ValueY() const {
      return pvValueY;
    }
    bool SetData( FileIperator& f_Begin, const FileIperator& f_End ) {
      return SetValue( f_Begin, f_End, pvValueX ) &&
        SetValue( f_Begin, f_End, pvValueY );
    }
  private:
    value_type pvValueX;
    value_type pvValueY;
    enum { Tag = DataType::ePair | CValueType < PCLTYPE >::ValueType };
  };
//******************************************************************************
  template < int PCLTYPE >
  class CData < DataType::eBox, PCLTYPE > : public CDataType {
  public:
    typedef typename CValueType< PCLTYPE >::value_type value_type;
    CData() : CDataType( Tag ), pvValueX1( 0 ), pvValueY1( 0 ),
      pvValueX2( 0 ), pvValueY2( 0 ) {};
    ~CData() {};
    enum { pcltype = DataType::eBox | CValueType < PCLTYPE >::ValueType };
    value_type& ValueX1() {
      return pvValueX1;
    }
    const value_type& ValueX1() const {
      return pvValueX1;
    }
    value_type& ValueY1() {
      return pvValueY1;
    }
    const value_type& ValueY1() const {
      return pvValueY1;
    }
    value_type& ValueX2() {
      return pvValueX2;
    }
    const value_type& ValueX2() const {
      return pvValueX2;
    }
    value_type& ValueY2() {
      return pvValueY2;
    }
    const value_type& ValueY2() const {
      return pvValueY2;
    }
    bool SetData( FileIperator& f_Begin, const FileIperator& f_End ) {
      return SetValue( f_Begin, f_End, pvValueX1 ) &&
        SetValue( f_Begin, f_End, pvValueY1 ) &&
        SetValue( f_Begin, f_End, pvValueX2 ) &&
        SetValue( f_Begin, f_End, pvValueY2 );
    }
  private:
    value_type pvValueX1;
    value_type pvValueY1;
    value_type pvValueX2;
    value_type pvValueY2;
    enum { Tag = DataType::eBox | CValueType < PCLTYPE >::ValueType };
  };
//******************************************************************************
  template < int PCLTYPE >
  class CData < DataType::eArray, PCLTYPE > : public CDataType {
  public:
    typedef typename CValueType< PCLTYPE >::value_type value_type;
      CData() : CDataType( Tag ) {};
    ~CData() {};
    value_type& operator[]( const std::size_t& f_Index ) {
      //return pvArray[f_Index]; // !!!;
      return 0;
    }
    const value_type& operator[]( const std::size_t& f_Index ) const {
      //return pvArray[f_Index]; // !!!
      return 0;
    }
    const std::size_t& Size() const {
      return 0;//pvSize;
    }
    bool SetData( FileIperator& f_Begin, const FileIperator& f_End ) {
      try {
        // initialize data of size of array;
        pvSize = CDataType::Create( *f_Begin++ );
        if( pvSize.get() && pvSize->SetData( f_Begin, f_End ) ) {
//          std::size_t t = pvSize->AsInteger();
//          std::cout << std::hex << "Byte count 0x" << t << std::endl;
          pvArray.resize( pvSize->AsInteger() );
          //s = pvArray.end() - pvArray.begin();
          std::generate( pvArray.begin(), pvArray.end(),
              CFillArray< value_type >( f_Begin, f_End ) );
          return f_Begin != f_End;
        }
        else{
          PCLErrno = PCLErr::ReadArrayData;
          return false;
        }
      }
      catch ( std::bad_alloc ) {
        PCLErrno = PCLErr::AllocateArray;
        return false;
      }
      // Is not implementation
      bool implementation = true;
      assert( not implementation );
      return false;
    }
  private:
    typedef typename std::vector< value_type > CDataArray;
    CDataTypePtr pvSize;
//    std::size_t pvSize;
    CDataArray pvArray;
    enum { Tag = DataType::eArray | CValueType < PCLTYPE >::ValueType };
  };
//******************************************************************************
  template < int PCLKIND, int PCLTYPE >
  inline CData< PCLKIND, PCLTYPE >* data_cast( CDataType* f_Data ){
    return dynamic_cast< CData< PCLKIND, PCLTYPE >* >( f_Data );
  }
//******************************************************************************

}; /* namespace pcl6 */

#endif /* __CDATA_HPP__ */

