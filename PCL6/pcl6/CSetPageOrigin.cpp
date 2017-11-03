//*****************************************************************************
//        File: CSetPageOrigin.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetPageOrigin.hpp"

namespace pcl6 {
//******************************************************************************
  CSetPageOrigin::CSetPageOrigin() : CPclOperator( PclTag::eSetPageOrigin ),
    pvPageOrigin( CreateAttribute< Attribute::ePageOrigin >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetPageOrigin::~CSetPageOrigin() {
  }
//******************************************************************************
  bool CSetPageOrigin::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvPageOrigin,
        0L );
  }
//******************************************************************************
  bool CSetPageOrigin::IsValid() const{
    return pvPageOrigin->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetPageOrigin::PageOrigin(){
    return this->pvPageOrigin;
  }
//******************************************************************************
  const CAttributePtr& CSetPageOrigin::PageOrigin() const{
    return this->pvPageOrigin;
  }

}
