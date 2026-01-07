//*****************************************************************************
//        File: CSetCharBoldValue.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCharBoldValue.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCharBoldValue::CSetCharBoldValue() : CPclOperator( PclTag::eSetCharBoldValue ),
    pvCharBoldValue( CreateAttribute< Attribute::eCharBoldValue >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCharBoldValue::~CSetCharBoldValue() {
  }
//******************************************************************************
  bool CSetCharBoldValue::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvCharBoldValue,
        0L );
  }
//******************************************************************************
  bool CSetCharBoldValue::IsValid() const{
    return pvCharBoldValue->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCharBoldValue::CharBoldValue(){
    return this->pvCharBoldValue;
  }
//******************************************************************************
  const CAttributePtr& CSetCharBoldValue::CharBoldValue() const{
    return this->pvCharBoldValue;
  }

}
