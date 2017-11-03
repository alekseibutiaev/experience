//*****************************************************************************
//        File: CSetCharScale.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCharScale.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCharScale::CSetCharScale() : CPclOperator( PclTag::eSetCharScale ),
    pvCharScale( CreateAttribute< Attribute::eCharScale >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCharScale::~CSetCharScale() {
  }
//******************************************************************************
  bool CSetCharScale::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvCharScale,
        0L );
  }
//******************************************************************************
  bool CSetCharScale::IsValid() const{
    return pvCharScale->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCharScale::CharScale(){
    return this->pvCharScale;
  }
//******************************************************************************
  const CAttributePtr& CSetCharScale::CharScale() const{
    return this->pvCharScale;
  }

}
