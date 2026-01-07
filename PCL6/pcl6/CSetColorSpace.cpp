//*****************************************************************************
//        File: CSetColorSpace.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetColorSpace.hpp"

namespace pcl6 {

//******************************************************************************
  CSetColorSpace::CSetColorSpace() : CPclOperator( PclTag::eSetColorSpace ),
    pvColorSpace( CreateAttribute< Attribute::eColorSpace >( AttributeIs::Obligatory ) ),
    pvPaletteData( CreateAttribute< Attribute::ePaletteData >( AttributeIs::Obligatory ) ),
    pvPaletteDepth( CreateAttribute< Attribute::ePaletteDepth >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetColorSpace::~CSetColorSpace() {
  }
//******************************************************************************
  bool CSetColorSpace::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvColorSpace,
        &pvPaletteData,
        &pvPaletteDepth,
        0L );
  }
//******************************************************************************
  bool CSetColorSpace::IsValid() const{
    return pvColorSpace->IsValid() || ( pvColorSpace->IsValid() &&
        pvPaletteData->IsValid() && pvColorSpace->IsValid() );
  }
//******************************************************************************
  CAttributePtr& CSetColorSpace::ColorSpace(){
    return this->pvColorSpace;
  }
//******************************************************************************
  const CAttributePtr& CSetColorSpace::ColorSpace() const{
    return this->pvColorSpace;
  }
//******************************************************************************
  CAttributePtr& CSetColorSpace::PaletteData(){
    return this->pvPaletteData;
  }
//******************************************************************************
  const CAttributePtr& CSetColorSpace::PaletteData() const {
    return this->pvPaletteData;
  }
//******************************************************************************
  CAttributePtr& CSetColorSpace::PaletteDepth(){
    return this->pvPaletteDepth;
  }
//******************************************************************************
  const CAttributePtr& CSetColorSpace::PaletteDepth()  const{
    return this->pvPaletteDepth;
  }

}; /* namespace pcl6 */
