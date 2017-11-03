//*****************************************************************************
//        File: CSetLineJoin.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetLineJoin.hpp"

namespace pcl6 {
//******************************************************************************
  CSetLineJoin::CSetLineJoin() : CPclOperator( PclTag::eSetLineJoin ),
    pvLineJoinStyle( CreateAttribute< Attribute::eLineJoinStyle >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetLineJoin::~CSetLineJoin() {
  }
//******************************************************************************
  bool CSetLineJoin::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvLineJoinStyle,
        0L );
  }
//******************************************************************************
  bool CSetLineJoin::IsValid() const{
    return pvLineJoinStyle->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetLineJoin::LineJoinStyle(){
    return this->pvLineJoinStyle;
  }
//******************************************************************************
  const CAttributePtr& CSetLineJoin::LineJoinStyle() const{
    return this->pvLineJoinStyle;
  }

}
