//*****************************************************************************
//        File: CSetPenWidth.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetPenWidth.hpp"

namespace pcl6 {
//******************************************************************************
  CSetPenWidth::CSetPenWidth() : CPclOperator( PclTag::eSetPenWidth ),
    pvPenWidth( CreateAttribute< Attribute::ePenWidth >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetPenWidth::~CSetPenWidth() {
  }
//******************************************************************************
  bool CSetPenWidth::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvPenWidth,
        0L );
  }
//******************************************************************************
  bool CSetPenWidth::IsValid() const{
    return pvPenWidth->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetPenWidth::PenWidth(){
    return this->pvPenWidth;
  }
//******************************************************************************
  const CAttributePtr& CSetPenWidth::PenWidth() const{
    return this->pvPenWidth;
  }

}
