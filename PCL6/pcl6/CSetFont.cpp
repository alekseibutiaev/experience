//*****************************************************************************
//        File: CSetFont.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetFont.hpp"

namespace pcl6 {

//******************************************************************************
  CSetFont::CSetFont() : CPclOperator( PclTag::eSetFont ),
    pvSymbolSet( CreateAttribute< Attribute::eSymbolSet >( AttributeIs::Obligatory ) ),
    pvCharSize( CreateAttribute< Attribute::eCharSize >( AttributeIs::Obligatory ) ),
    pvFontName( CreateAttribute< Attribute::eFontName >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetFont::~CSetFont() {
  }
//******************************************************************************
  bool CSetFont::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvSymbolSet,
        &pvCharSize,
        &pvFontName,
        0L );
  }
//******************************************************************************
  bool CSetFont::IsValid() const{
    return pvSymbolSet->IsValid() && pvCharSize->IsValid() &&
      pvFontName->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetFont::SymbolSet(){
    return this->pvSymbolSet;
  }
//******************************************************************************
  const CAttributePtr& CSetFont::SymbolSet() const{
    return this->pvSymbolSet;
  }
//******************************************************************************
  CAttributePtr& CSetFont::CharSize(){
    return this->pvCharSize;
  }
//******************************************************************************
  const CAttributePtr& CSetFont::CharSize() const {
    return this->pvCharSize;
  }
//******************************************************************************
  CAttributePtr& CSetFont::FontName(){
    return this->pvFontName;
  }
//******************************************************************************
  const CAttributePtr& CSetFont::FontName()  const{
    return this->pvFontName;
  }

}; /* namespace pcl6 */
