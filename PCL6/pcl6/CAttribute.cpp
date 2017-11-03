//*****************************************************************************
//        File: CAttribute.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CAttribute.hpp"
#include "CAttributeTag.hpp"

namespace pcl6 {

//******************************************************************************
  CAttribute::CAttribute( const int& f_Tag, AttributeIs::Status f_Status ) :
    CBaseTag( f_Tag ), pvStatus( f_Status ) {
  }
//******************************************************************************
  CAttribute::~CAttribute(){
  }
//******************************************************************************
  CDataTypePtr& CAttribute::Data() {
    return pvData;
  }
//******************************************************************************
  const CDataTypePtr& CAttribute::Data() const {
    return pvData;
  }
//******************************************************************************
  bool CAttribute::IsValid() const{
    return pvData.get() || pvStatus == AttributeIs::Optional;
  }
//******************************************************************************
  bool CAttribute::IsSet() const{
    return pvData.get();
  }
//******************************************************************************
  CAttributePtr CAttribute::Create( const Byte& f_AttributeTag,
      AttributeIs::Status f_Status ) {
    switch ( f_AttributeTag ){
      case AttributeTag::eAttr8 :
        return CAttributePtr( new CAttributeTag< AttributeTag::eAttr8 >() );
      case AttributeTag::eAttr16 :
        return CAttributePtr( new CAttributeTag< AttributeTag::eAttr16 >() );
      default:
        return CAttributePtr();
    }
  }

}; /* namespace pcl6 */
