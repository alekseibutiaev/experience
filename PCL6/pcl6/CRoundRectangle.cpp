//*****************************************************************************
//        File: CRoundRectangle.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CRoundRectangle.hpp"

namespace pcl6 {

//******************************************************************************
  CRoundRectangle::CRoundRectangle() : CPclOperator( PclTag::eRoundRectangle ),
    pvEllipseDimension( CreateAttribute< Attribute::eEllipseDimension >( AttributeIs::Obligatory ) ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CRoundRectangle::~CRoundRectangle() {
  }
//******************************************************************************
  bool CRoundRectangle::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvEllipseDimension,
        &pvBoundingBox,
        0L );
  }
//******************************************************************************
  bool CRoundRectangle::IsValid() const{
    return pvEllipseDimension->IsValid() && pvBoundingBox->IsValid();
  }
//******************************************************************************
  CAttributePtr& CRoundRectangle::EllipseDimension(){
    return this->pvEllipseDimension;
  }
//******************************************************************************
  const CAttributePtr& CRoundRectangle::EllipseDimension() const{
    return this->pvEllipseDimension;
  }
//******************************************************************************
  CAttributePtr& CRoundRectangle::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CRoundRectangle::BoundingBox() const {
    return this->pvBoundingBox;
  }

}; /* namespace pcl6 */
