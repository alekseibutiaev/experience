//*****************************************************************************
//        File: CSetSourceTxMode.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetSourceTxMode.hpp"

namespace pcl6 {
//******************************************************************************
  CSetSourceTxMode::CSetSourceTxMode() : CPclOperator( PclTag::eSetSourceTxMode ),
    pvTxMode( CreateAttribute< Attribute::eTxMode >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetSourceTxMode::~CSetSourceTxMode() {
  }
//******************************************************************************
  bool CSetSourceTxMode::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvTxMode,
        0L );
  }
//******************************************************************************
  bool CSetSourceTxMode::IsValid() const{
    return pvTxMode->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetSourceTxMode::TxMode(){
    return this->pvTxMode;
  }
//******************************************************************************
  const CAttributePtr& CSetSourceTxMode::TxMode() const{
    return this->pvTxMode;
  }

}
