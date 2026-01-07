//*****************************************************************************
//        File: CSetClipMode.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetClipMode.hpp"

namespace pcl6 {
//******************************************************************************
  CSetClipMode::CSetClipMode() : CPclOperator( PclTag::eSetClipMode ),
    pvClipMode( CreateAttribute< Attribute::eClipMode >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetClipMode::~CSetClipMode() {
  }
//******************************************************************************
  bool CSetClipMode::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvClipMode,
        0L );
  }
//******************************************************************************
  bool CSetClipMode::IsValid() const{
    return pvClipMode->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetClipMode::ClipMode(){
    return this->pvClipMode;
  }
//******************************************************************************
  const CAttributePtr& CSetClipMode::ClipMode() const{
    return this->pvClipMode;
  }

}
