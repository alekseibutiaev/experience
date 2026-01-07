//*****************************************************************************
//        File: CSetCharShear.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCharShear.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCharShear::CSetCharShear() : CPclOperator( PclTag::eSetCharShear ),
    pvCharShear( CreateAttribute< Attribute::eCharShear >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCharShear::~CSetCharShear() {
  }
//******************************************************************************
  bool CSetCharShear::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvCharShear,
        0L );
  }
//******************************************************************************
  bool CSetCharShear::IsValid() const{
    return pvCharShear->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCharShear::CharShear(){
    return this->pvCharShear;
  }
//******************************************************************************
  const CAttributePtr& CSetCharShear::CharShear() const{
    return this->pvCharShear;
  }

}
