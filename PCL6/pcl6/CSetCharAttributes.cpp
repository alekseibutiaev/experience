//*****************************************************************************
//        File: CSetCharAttributes.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCharAttributes.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCharAttributes::CSetCharAttributes() : CPclOperator( PclTag::eSetCharAttributes ),
    pvClipMode( CreateAttribute< Attribute::eClipMode >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCharAttributes::~CSetCharAttributes() {
  }
//******************************************************************************
  bool CSetCharAttributes::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvClipMode,
        0L );
  }
//******************************************************************************
  bool CSetCharAttributes::IsValid() const{
    return pvClipMode->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCharAttributes::ClipMode(){
    return this->pvClipMode;
  }
//******************************************************************************
  const CAttributePtr& CSetCharAttributes::ClipMode() const{
    return this->pvClipMode;
  }

}
