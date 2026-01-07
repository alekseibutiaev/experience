//*****************************************************************************
//        File: CRemoveFont.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CRemoveFont.hpp"

namespace pcl6 {
//******************************************************************************
  CRemoveFont::CRemoveFont() : CPclOperator( PclTag::eRemoveFont ),
    pvFontName( CreateAttribute< Attribute::eFontName >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CRemoveFont::~CRemoveFont() {
  }
//******************************************************************************
  bool CRemoveFont::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvFontName,
        0L );
  }
//******************************************************************************
  bool CRemoveFont::IsValid() const{
    return pvFontName->IsValid();
  }
//******************************************************************************
  CAttributePtr& CRemoveFont::FontName(){
    return this->pvFontName;
  }
//******************************************************************************
  const CAttributePtr& CRemoveFont::FontName() const{
    return this->pvFontName;
  }

}
