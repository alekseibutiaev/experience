//*****************************************************************************
//        File: CText.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CText.hpp"

namespace pcl6 {

//******************************************************************************
  CText::CText() : CPclOperator( PclTag::eText ),
    pvTextData( CreateAttribute< Attribute::eTextData >( AttributeIs::Obligatory ) ),
    pvYSpacingData( CreateAttribute< Attribute::eYSpacingData >( AttributeIs::Optional ) ),
    pvXSpacingData( CreateAttribute< Attribute::eXSpacingData >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CText::~CText() {
  }
//******************************************************************************
  bool CText::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvTextData,
        &pvYSpacingData,
        &pvXSpacingData,
        0L );
  }
//******************************************************************************
  bool CText::IsValid() const{
    return pvTextData->IsValid() && pvYSpacingData->IsValid() &&
      pvXSpacingData->IsValid();
  }
//******************************************************************************
  CAttributePtr& CText::TextData(){
    return this->pvTextData;
  }
//******************************************************************************
  const CAttributePtr& CText::TextData() const{
    return this->pvTextData;
  }
//******************************************************************************
  CAttributePtr& CText::YSpacingData(){
    return this->pvYSpacingData;
  }
//******************************************************************************
  const CAttributePtr& CText::YSpacingData() const {
    return this->pvYSpacingData;
  }
//******************************************************************************
  CAttributePtr& CText::XSpacingData(){
    return this->pvXSpacingData;
  }
//******************************************************************************
  const CAttributePtr& CText::XSpacingData()  const{
    return this->pvXSpacingData;
  }

}; /* namespace pcl6 */
