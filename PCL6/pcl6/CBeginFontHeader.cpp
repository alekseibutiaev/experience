//*****************************************************************************
//        File: CBeginFontHeader.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBeginFontHeader.hpp"

namespace pcl6 {
//******************************************************************************
  CBeginFontHeader::CBeginFontHeader() : CPclOperator( PclTag::eBeginFontHeader ),
    pvFontName( CreateAttribute< Attribute::eFontName >( AttributeIs::Obligatory ) ),
    pvFontFormat( CreateAttribute< Attribute::eFontFormat >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBeginFontHeader::~CBeginFontHeader() {
  }
//******************************************************************************
  bool CBeginFontHeader::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvFontName,
        &pvFontFormat,
        0L );
  }
//******************************************************************************
  bool CBeginFontHeader::IsValid() const{
    return pvFontName->IsValid() && pvFontFormat->IsValid();
  }
//******************************************************************************
  CAttributePtr& CBeginFontHeader::FontName(){
    return this->pvFontName;
  }
//******************************************************************************
  const CAttributePtr& CBeginFontHeader::FontName() const{
    return this->pvFontName;
  }
  //******************************************************************************
    CAttributePtr& CBeginFontHeader::FontFormat(){
      return this->pvFontFormat;
    }
  //******************************************************************************
    const CAttributePtr& CBeginFontHeader::FontFormat() const{
      return this->pvFontFormat;
    }

}
