//*****************************************************************************
//        File: ParserFunction.cpp
//     Project: kopirkin
//  Created on: 04.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "ParserErrno.hpp"
#include "ParserFunction.hpp"

namespace pcl6{

//*****************************************************************************
  bool ReadData( FileIperator& f_Begin, const FileIperator& f_End,
      CDataTypePtr& f_Result ){
    // Try getting data
    f_Result = CDataType::Create( *f_Begin );
    // current position is data
    if( f_Result.get() ){
      ++f_Begin;
      // current data is not set and set data from next position is success.
      if( f_Result->SetData( f_Begin, f_End ) )
        return true;
      PCLErrno = PCLErr::InvalidData;
    }
    return false;
  }
//*****************************************************************************
  bool ReadAttribute( FileIperator& f_Begin, const FileIperator& f_End,
      CAttributePtr& f_Result ) {

    // Try getting attribute
    CAttributePtr isAttribute( CAttribute::Create( *f_Begin ) );
    if( isAttribute.get() ) {
      // set attribute ID from next position
      ++f_Begin;
      if( !isAttribute->SetAttributeID( f_Begin, f_End ) ){
        PCLErrno = PCLErr::InvalidAttrID;
        return false;
      }
      // return attribute
      f_Result = isAttribute;
      return true;
    }
    return false;
  }
//*****************************************************************************
  bool ReadPcl( FileIperator& f_Begin, const FileIperator& f_End,
      CAttributeArray& f_Attribute, COperatorPtr& f_Result ) {
    CPclOperatorPtr isPcl( CPclOperator::Create( *f_Begin ) );
    if( isPcl.get() ){
      ++f_Begin;
      if( isPcl->SetAttributes( f_Attribute ) ){
        // return new operator
        f_Result = isPcl;
        return true;
      }
      PCLErrno = PCLErr::InvalidAttrSet;
    }
    return false;
  }
//*****************************************************************************
  bool ReadPjl( FileIperator& f_Begin, const FileIperator& f_End,
      COperatorPtr& f_Result ){
    CPjlOperatorPtr isPjl( CPjlOperator::Create( *f_Begin ) );
    if( isPjl.get() ) {
      if( isPjl->SetString( f_Begin, f_End ) ) {
        // return new operator
        f_Result = isPjl;
        return true;
      }
      PCLErrno = PCLErr::InvalidStrOpr;
    }
    return false;
  }
//*****************************************************************************
  bool ReadEmbedData( FileIperator& f_Begin, const FileIperator& f_End,
      COperatorPtr& f_Result ) {
    CEmbedTypePtr isEmbedType( CEmbedType::Create( *f_Begin ) );
    if( isEmbedType.get() ){
      ++f_Begin;
      if( isEmbedType->ReadData( f_Begin, f_End ) ){
        ++f_Begin;
        f_Result = isEmbedType;
        return true;
      }
      PCLErrno = PCLErr::InvalidEmbData;
    }
    return false;
  }
//*****************************************************************************

}; /* namespace pcl6 */
