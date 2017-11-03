//*****************************************************************************
//        File: CEmbedData.hpp
//     Project: kopirkin
//  Created on: 04.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CEMBEDDATA_HPP__
#define __CEMBEDDATA_HPP__

#include <vector>
#include <algorithm>
#include <cassert>

#include "StaticIf.hpp"
#include "CValueType.hpp"
#include "CEmbedType.hpp"

namespace pcl6 {

  template< int EMBEDTYPE >
  class CEmbedData : public CEmbedType {
  public:
    CEmbedData() : CEmbedType( EMBEDTYPE ), pvSize( 0 ){};
    ~CEmbedData(){};
    bool ReadData( FileIperator& f_Begin, const FileIperator& f_End ){
//      bool Tested = true;
//      assert( not Tested );
      SetValue( f_Begin, f_End, pvSize );
      if( pvSize ) {
        while( f_Begin != f_End && --pvSize )
          pvArray.push_back( *f_Begin++ );
        return f_Begin != f_End;
      }
      return false;
    }
    bool IsValid() const{
      return pvArray.size();
    }
    const std::size_t Size() const{
      return pvArray.size();
    }
  private:
//    typedef CValueType< Value::eUbyte > CByte;
//    typedef CValueType< Value::eUint32 > CInteger;
    typedef typename if_c< EMBEDTYPE == EmbedData::eDataLength,
        unsigned int, unsigned char >::type size_type;
    typedef std::vector< Byte > CEmbedArray;
    size_type pvSize;
    CEmbedArray pvArray;
  };
}; /* namespace pcl6 */

#endif /* __CEMBEDDATA_HPP__ */
