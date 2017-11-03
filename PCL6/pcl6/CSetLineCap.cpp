//*****************************************************************************
//        File: CSetLineCap.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetLineCap.hpp"

namespace pcl6 {
//******************************************************************************
  CSetLineCap::CSetLineCap() : CPclOperator( PclTag::eSetLineCap ),
    pvLineCapStyle( CreateAttribute< Attribute::eLineCapStyle >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetLineCap::~CSetLineCap() {
  }
//******************************************************************************
  bool CSetLineCap::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvLineCapStyle,
        0L );
  }
//******************************************************************************
  bool CSetLineCap::IsValid() const{
    return pvLineCapStyle->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetLineCap::LineCapStyle(){
    return this->pvLineCapStyle;
  }
//******************************************************************************
  const CAttributePtr& CSetLineCap::LineCapStyle() const{
    return this->pvLineCapStyle;
  }

}
