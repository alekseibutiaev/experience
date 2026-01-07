//*****************************************************************************
//        File: CEllipsePath.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CEllipsePath.hpp"

namespace pcl6 {
//******************************************************************************
  CEllipsePath::CEllipsePath() : CPclOperator( PclTag::eEllipsePath ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CEllipsePath::~CEllipsePath() {
  }
//******************************************************************************
  bool CEllipsePath::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        0L );
  }
//******************************************************************************
  bool CEllipsePath::IsValid() const{
    return pvBoundingBox->IsValid();
  }
//******************************************************************************
  CAttributePtr& CEllipsePath::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CEllipsePath::BoundingBox() const{
    return this->pvBoundingBox;
  }

}
