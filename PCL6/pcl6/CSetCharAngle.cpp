//*****************************************************************************
//        File: CSetCharAngle.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCharAngle.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCharAngle::CSetCharAngle() : CPclOperator( PclTag::eSetCharAngle ),
    pvCharAngle( CreateAttribute< Attribute::eCharAngle >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCharAngle::~CSetCharAngle() {
  }
//******************************************************************************
  bool CSetCharAngle::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvCharAngle,
        0L );
  }
//******************************************************************************
  bool CSetCharAngle::IsValid() const{
    return pvCharAngle->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCharAngle::CharAngle(){
    return this->pvCharAngle;
  }
//******************************************************************************
  const CAttributePtr& CSetCharAngle::CharAngle() const{
    return this->pvCharAngle;
  }

}
