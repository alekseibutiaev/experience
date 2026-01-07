//*****************************************************************************
//        File: CSetCursor.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCursor.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCursor::CSetCursor() : CPclOperator( PclTag::eSetCursor ),
    pvPoint( CreateAttribute< Attribute::ePoint >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCursor::~CSetCursor() {
  }
//******************************************************************************
  bool CSetCursor::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvPoint,
        0L );
  }
//******************************************************************************
  bool CSetCursor::IsValid() const{
    return pvPoint->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCursor::Point(){
    return this->pvPoint;
  }
//******************************************************************************
  const CAttributePtr& CSetCursor::Point() const{
    return this->pvPoint;
  }

}
