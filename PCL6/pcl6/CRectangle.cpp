//*****************************************************************************
//        File: CRectangle.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CRectangle.hpp"

namespace pcl6 {
//******************************************************************************
  CRectangle::CRectangle() : CPclOperator( PclTag::eRectangle ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CRectangle::~CRectangle() {
  }
//******************************************************************************
  bool CRectangle::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        0L );
  }
//******************************************************************************
  bool CRectangle::IsValid() const{
    return pvBoundingBox->IsValid();
  }
//******************************************************************************
  CAttributePtr& CRectangle::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CRectangle::BoundingBox() const{
    return this->pvBoundingBox;
  }

}
