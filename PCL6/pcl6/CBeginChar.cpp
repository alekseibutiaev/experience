//*****************************************************************************
//        File: CBeginChar.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBeginChar.hpp"

namespace pcl6 {
//******************************************************************************
  CBeginChar::CBeginChar() : CPclOperator( PclTag::eBeginChar ),
    pvFontName( CreateAttribute< Attribute::eFontName >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBeginChar::~CBeginChar() {
  }
//******************************************************************************
  bool CBeginChar::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvFontName,
        0L );
  }
//******************************************************************************
  bool CBeginChar::IsValid() const{
    return pvFontName->IsValid();
  }
//******************************************************************************
  CAttributePtr& CBeginChar::FontName(){
    return this->pvFontName;
  }
//******************************************************************************
  const CAttributePtr& CBeginChar::FontName() const{
    return this->pvFontName;
  }

}
