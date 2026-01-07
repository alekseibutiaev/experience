//*****************************************************************************
//        File: CSetFillMode.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetFillMode.hpp"

namespace pcl6 {
//******************************************************************************
  CSetFillMode::CSetFillMode() : CPclOperator( PclTag::eSetFillMode ),
    pvFillMode( CreateAttribute< Attribute::eFillMode >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetFillMode::~CSetFillMode() {
  }
//******************************************************************************
  bool CSetFillMode::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvFillMode,
        0L );
  }
//******************************************************************************
  bool CSetFillMode::IsValid() const{
    return pvFillMode->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetFillMode::FillMode(){
    return this->pvFillMode;
  }
//******************************************************************************
  const CAttributePtr& CSetFillMode::FillMode() const{
    return this->pvFillMode;
  }

}
