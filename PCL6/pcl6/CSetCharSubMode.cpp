//*****************************************************************************
//        File: CSetCharSubMode.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCharSubMode.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCharSubMode::CSetCharSubMode() : CPclOperator( PclTag::eSetCharSubMode ),
    pvCharSubModeArray( CreateAttribute< Attribute::eCharSubModeArray >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCharSubMode::~CSetCharSubMode() {
  }
//******************************************************************************
  bool CSetCharSubMode::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvCharSubModeArray,
        0L );
  }
//******************************************************************************
  bool CSetCharSubMode::IsValid() const{
    return pvCharSubModeArray->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCharSubMode::CharSubModeArray(){
    return this->pvCharSubModeArray;
  }
//******************************************************************************
  const CAttributePtr& CSetCharSubMode::CharSubModeArray() const{
    return this->pvCharSubModeArray;
  }

}
