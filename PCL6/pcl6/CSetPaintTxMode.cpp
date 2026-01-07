//*****************************************************************************
//        File: CSetPaintTxMode.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetPaintTxMode.hpp"

namespace pcl6 {
//******************************************************************************
  CSetPaintTxMode::CSetPaintTxMode() : CPclOperator( PclTag::eSetPaintTxMode ),
    pvTxMode( CreateAttribute< Attribute::eTxMode >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetPaintTxMode::~CSetPaintTxMode() {
  }
//******************************************************************************
  bool CSetPaintTxMode::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvTxMode,
        0L );
  }
//******************************************************************************
  bool CSetPaintTxMode::IsValid() const{
    return pvTxMode->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetPaintTxMode::TxMode(){
    return this->pvTxMode;
  }
//******************************************************************************
  const CAttributePtr& CSetPaintTxMode::TxMode() const{
    return this->pvTxMode;
  }

}
