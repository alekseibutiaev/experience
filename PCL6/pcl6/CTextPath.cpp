//*****************************************************************************
//        File: CTextPath.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CTextPath.hpp"

namespace pcl6 {

//******************************************************************************
  CTextPath::CTextPath() : CPclOperator( PclTag::eTextPath ),
    pvXSpacingData( CreateAttribute< Attribute::eXSpacingData >( AttributeIs::Optional ) ),
    pvYSpacingData( CreateAttribute< Attribute::eYSpacingData >( AttributeIs::Optional ) ),
    pvTextData( CreateAttribute< Attribute::eTextData >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CTextPath::~CTextPath() {
  }
//******************************************************************************
  bool CTextPath::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvXSpacingData,
        &pvYSpacingData,
        &pvTextData,
        0L );
  }
//******************************************************************************
  bool CTextPath::IsValid() const{
    return pvXSpacingData->IsValid() && pvYSpacingData->IsValid() &&
      pvTextData->IsValid();
  }
//******************************************************************************
  CAttributePtr& CTextPath::XSpacingData(){
    return this->pvXSpacingData;
  }
//******************************************************************************
  const CAttributePtr& CTextPath::XSpacingData() const{
    return this->pvXSpacingData;
  }
//******************************************************************************
  CAttributePtr& CTextPath::YSpacingData(){
    return this->pvYSpacingData;
  }
//******************************************************************************
  const CAttributePtr& CTextPath::YSpacingData() const {
    return this->pvYSpacingData;
  }
//******************************************************************************
  CAttributePtr& CTextPath::TextData(){
    return this->pvTextData;
  }
//******************************************************************************
  const CAttributePtr& CTextPath::TextData()  const{
    return this->pvTextData;
  }

}; /* namespace pcl6 */
