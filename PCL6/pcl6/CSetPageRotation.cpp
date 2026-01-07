//*****************************************************************************
//        File: CSetPageRotation.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetPageRotation.hpp"

namespace pcl6 {
//******************************************************************************
  CSetPageRotation::CSetPageRotation() : CPclOperator( PclTag::eSetPageRotation ),
    pvPageAngle ( CreateAttribute< Attribute::ePageAngle  >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetPageRotation::~CSetPageRotation() {
  }
//******************************************************************************
  bool CSetPageRotation::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvPageAngle ,
        0L );
  }
//******************************************************************************
  bool CSetPageRotation::IsValid() const{
    return pvPageAngle ->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetPageRotation::PageAngle (){
    return this->pvPageAngle ;
  }
//******************************************************************************
  const CAttributePtr& CSetPageRotation::PageAngle () const{
    return this->pvPageAngle ;
  }

}
