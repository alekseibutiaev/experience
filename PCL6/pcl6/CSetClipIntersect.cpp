//*****************************************************************************
//        File: CSetClipIntersect.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetClipIntersect.hpp"

namespace pcl6 {
//******************************************************************************
  CSetClipIntersect::CSetClipIntersect() : CPclOperator( PclTag::eSetClipIntersect ),
    pvClipRegion( CreateAttribute< Attribute::eClipRegion >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetClipIntersect::~CSetClipIntersect() {
  }
//******************************************************************************
  bool CSetClipIntersect::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvClipRegion,
        0L );
  }
//******************************************************************************
  bool CSetClipIntersect::IsValid() const{
    return pvClipRegion->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetClipIntersect::ClipRegion(){
    return this->pvClipRegion;
  }
//******************************************************************************
  const CAttributePtr& CSetClipIntersect::ClipRegion() const{
    return this->pvClipRegion;
  }

}
