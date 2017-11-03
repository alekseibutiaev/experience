//*****************************************************************************
//        File: CSetMiterLimit.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetMiterLimit.hpp"

namespace pcl6 {
//******************************************************************************
  CSetMiterLimit::CSetMiterLimit() : CPclOperator( PclTag::eSetMiterLimit ),
    pvMiterLength ( CreateAttribute< Attribute::eMiterLength  >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetMiterLimit::~CSetMiterLimit() {
  }
//******************************************************************************
  bool CSetMiterLimit::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvMiterLength ,
        0L );
  }
//******************************************************************************
  bool CSetMiterLimit::IsValid() const{
    return pvMiterLength ->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetMiterLimit::MiterLength (){
    return this->pvMiterLength ;
  }
//******************************************************************************
  const CAttributePtr& CSetMiterLimit::MiterLength () const{
    return this->pvMiterLength ;
  }

}
