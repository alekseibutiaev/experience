//*****************************************************************************
//        File: CSetCursorRel.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetCursorRel.hpp"

namespace pcl6 {
//******************************************************************************
  CSetCursorRel::CSetCursorRel() : CPclOperator( PclTag::eSetCursorRel ),
    pvPoint( CreateAttribute< Attribute::ePoint >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetCursorRel::~CSetCursorRel() {
  }
//******************************************************************************
  bool CSetCursorRel::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvPoint,
        0L );
  }
//******************************************************************************
  bool CSetCursorRel::IsValid() const{
    return pvPoint->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetCursorRel::Point(){
    return this->pvPoint;
  }
//******************************************************************************
  const CAttributePtr& CSetCursorRel::Point() const{
    return this->pvPoint;
  }

}
