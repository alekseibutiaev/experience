//*****************************************************************************
//        File: CEllipse.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CEllipse.hpp"

namespace pcl6 {
//******************************************************************************
  CEllipse::CEllipse() : CPclOperator( PclTag::eEllipse ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CEllipse::~CEllipse() {
  }
//******************************************************************************
  bool CEllipse::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        0L );
  }
//******************************************************************************
  bool CEllipse::IsValid() const{
    return pvBoundingBox->IsValid();
  }
//******************************************************************************
  CAttributePtr& CEllipse::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CEllipse::BoundingBox() const{
    return this->pvBoundingBox;
  }

}
