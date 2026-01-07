//*****************************************************************************
//        File: CSetClipRectangle.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetClipRectangle.hpp"

namespace pcl6 {
//******************************************************************************
  CSetClipRectangle::CSetClipRectangle() : CPclOperator( PclTag::eSetClipRectangle ),
    pvClipRegion( CreateAttribute< Attribute::eClipRegion >( AttributeIs::Obligatory ) ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetClipRectangle::~CSetClipRectangle() {
  }
//******************************************************************************
  bool CSetClipRectangle::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvClipRegion,
        &pvBoundingBox,
        0L );
  }
//******************************************************************************
  bool CSetClipRectangle::IsValid() const{
    return pvClipRegion->IsValid() && pvBoundingBox->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetClipRectangle::ClipRegion(){
    return this->pvClipRegion;
  }
//******************************************************************************
  const CAttributePtr& CSetClipRectangle::ClipRegion() const{
    return this->pvClipRegion;
  }
//******************************************************************************
  CAttributePtr& CSetClipRectangle::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CSetClipRectangle::BoundingBox() const{
    return this->pvBoundingBox;
  }

}
