//*****************************************************************************
//        File: CReadChar.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CReadChar.hpp"

namespace pcl6 {
//******************************************************************************
  CReadChar::CReadChar() : CPclOperator( PclTag::eReadChar ),
    pvCharCode( CreateAttribute< Attribute::eCharCode >( AttributeIs::Obligatory ) ),
    pvCharDataSize( CreateAttribute< Attribute::eCharDataSize >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CReadChar::~CReadChar() {
  }
//******************************************************************************
  bool CReadChar::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvCharCode,
        &pvCharDataSize,
        0L );
  }
//******************************************************************************
  bool CReadChar::IsValid() const{
    return pvCharCode->IsValid() && pvCharDataSize->IsValid();
  }
//******************************************************************************
  CAttributePtr& CReadChar::CharCode(){
    return this->pvCharCode;
  }
//******************************************************************************
  const CAttributePtr& CReadChar::CharCode() const{
    return this->pvCharCode;
  }
//******************************************************************************
  CAttributePtr& CReadChar::CharDataSize(){
    return this->pvCharDataSize;
  }
//******************************************************************************
  const CAttributePtr& CReadChar::CharDataSize() const{
    return this->pvCharDataSize;
  }

}
