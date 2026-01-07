//*****************************************************************************
//        File: CSetROP.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetROP.hpp"

namespace pcl6 {
//******************************************************************************
  CSetROP::CSetROP() : CPclOperator( PclTag::eSetROP ),
    pvROP( CreateAttribute< Attribute::eROP3 >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetROP::~CSetROP() {
  }
//******************************************************************************
  bool CSetROP::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvROP,
        0L );
  }
//******************************************************************************
  bool CSetROP::IsValid() const{
    return pvROP->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetROP::ROP(){
    return this->pvROP;
  }
//******************************************************************************
  const CAttributePtr& CSetROP::ROP() const{
    return this->pvROP;
  }

}
