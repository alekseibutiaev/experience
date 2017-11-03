//*****************************************************************************
//        File: CReadFontHeader.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CReadFontHeader.hpp"

namespace pcl6 {
//******************************************************************************
  CReadFontHeader::CReadFontHeader() : CPclOperator( PclTag::eReadFontHeader ),
    pvFontHeaderLength( CreateAttribute< Attribute::eFontHeaderLength >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CReadFontHeader::~CReadFontHeader() {
  }
//******************************************************************************
  bool CReadFontHeader::SetAttributes( const CAttributeArray& f_Atributes ){
     return ptSetAttributes( f_Atributes,
        &pvFontHeaderLength,
        0L );
  }
//******************************************************************************
  bool CReadFontHeader::IsValid() const{
    return pvFontHeaderLength->IsValid();
  }
//******************************************************************************
  CAttributePtr& CReadFontHeader::FontHeaderLength(){
    return this->pvFontHeaderLength;
  }
//******************************************************************************
  const CAttributePtr& CReadFontHeader::FontHeaderLength() const{
    return this->pvFontHeaderLength;
  }

}
