//*****************************************************************************
//        File: CSetPageScale.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetPageScale.hpp"

namespace pcl6 {
//******************************************************************************
  CSetPageScale::CSetPageScale() : CPclOperator( PclTag::eSetPageScale ),
    pvPageScale( CreateAttribute< Attribute::ePageScale >( AttributeIs::Obligatory ) ),
    pvMeasure( CreateAttribute< Attribute::eMeasure >( AttributeIs::Obligatory ) ),
    pvUnitsPerMeasure( CreateAttribute< Attribute::eUnitsPerMeasure >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetPageScale::~CSetPageScale() {
  }
//******************************************************************************
  bool CSetPageScale::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvPageScale,
        &pvMeasure,
        &pvUnitsPerMeasure,
        0L );
  }
//******************************************************************************
  bool CSetPageScale::IsValid() const{
    return pvPageScale->IsValid() ||
      ( pvMeasure->IsValid() && pvUnitsPerMeasure->IsValid() );
  }
//******************************************************************************
  CAttributePtr& CSetPageScale::PageScale(){
    return pvPageScale;
  }
//******************************************************************************
  const CAttributePtr& CSetPageScale::PageScale() const{
    return pvPageScale;
  }
//******************************************************************************
  CAttributePtr& CSetPageScale::Measure(){
    return pvMeasure;
  }
//******************************************************************************
  const CAttributePtr& CSetPageScale::Measure() const{
    return pvMeasure;
  }
//******************************************************************************
  CAttributePtr& CSetPageScale::UnitsPerMeasure(){
    return pvUnitsPerMeasure;
  }
//******************************************************************************
  const CAttributePtr& CSetPageScale::UnitsPerMeasure() const{
    return pvUnitsPerMeasure;
  }

}
