//*****************************************************************************
//        File: CSetClipReplace.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetClipReplace.hpp"

namespace pcl6 {
//******************************************************************************
  CSetClipReplace::CSetClipReplace() : CPclOperator( PclTag::eSetClipReplace ),
    pvClipRegion( CreateAttribute< Attribute::eClipRegion >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetClipReplace::~CSetClipReplace() {
  }
//******************************************************************************
  bool CSetClipReplace::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvClipRegion,
        0L );
  }
//******************************************************************************
  bool CSetClipReplace::IsValid() const{
    return pvClipRegion->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetClipReplace::ClipRegion(){
    return this->pvClipRegion;
  }
//******************************************************************************
  const CAttributePtr& CSetClipReplace::ClipRegion() const{
    return this->pvClipRegion;
  }

}
