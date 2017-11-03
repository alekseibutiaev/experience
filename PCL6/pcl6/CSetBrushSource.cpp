//*****************************************************************************
//        File: CSetBrushSource.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetBrushSource.hpp"

namespace pcl6 {

//******************************************************************************
  CSetBrushSource::CSetBrushSource() : CPclOperator( PclTag::eSetBrushSource ),
    pvRGBColor( CreateAttribute< Attribute::eRGBColor >( AttributeIs::Obligatory ) ),
    pvGrayLevel( CreateAttribute< Attribute::eGrayLevel >( AttributeIs::Obligatory ) ),
    pvNullBrush( CreateAttribute< Attribute::eNullBrush >( AttributeIs::Obligatory ) ),
    pvPrimaryArray( CreateAttribute< Attribute::ePrimaryArray >( AttributeIs::Obligatory ) ),
    pvPrimaryDepth( CreateAttribute< Attribute::ePrimaryDepth >( AttributeIs::Obligatory ) ),
    pvPatternSelectID( CreateAttribute< Attribute::ePatternSelectID >( AttributeIs::Obligatory ) ),
    pvPatternOrigin( CreateAttribute< Attribute::ePatternOrigin >( AttributeIs::Optional ) ),
    pvNewDestinationSize( CreateAttribute< Attribute::eNewDestinationSize >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetBrushSource::~CSetBrushSource() {
  }
//******************************************************************************
  bool CSetBrushSource::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvRGBColor,
        &pvGrayLevel,
        &pvNullBrush,
        &pvPrimaryArray,
        &pvPrimaryDepth,
        &pvPatternSelectID,
        &pvPatternOrigin,
        &pvNewDestinationSize,
        0L );
  }
//******************************************************************************
  bool CSetBrushSource::IsValid() const{
    return pvRGBColor->IsValid() || pvGrayLevel->IsValid() ||
      ( pvPrimaryArray->IsValid() && pvPrimaryDepth->IsValid() ) ||
        pvNullBrush->IsValid() ||
        ( pvPatternSelectID->IsValid() &&
            ( pvPatternOrigin->IsValid() && pvNewDestinationSize->IsValid() ) );
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::RGBColor(){
    return this->pvRGBColor;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::RGBColor() const{
    return this->pvRGBColor;
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::GrayLevel(){
    return this->pvGrayLevel;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::GrayLevel() const {
    return this->pvGrayLevel;
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::NullBrush(){
    return this->pvNullBrush;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::NullBrush()  const{
    return this->pvNullBrush;
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::PrimaryArray(){
    return this->pvPrimaryArray;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::PrimaryArray() const{
    return this->pvPrimaryArray;
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::PrimaryDepth(){
    return this->pvPrimaryDepth;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::PrimaryDepth() const{
    return this->pvPrimaryDepth;
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::PatternSelectID(){
    return this->pvPatternSelectID;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::PatternSelectID() const{
    return this->pvPatternSelectID;
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::PatternOrigin(){
    return this->pvPatternOrigin;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::PatternOrigin() const{
    return this->pvPatternOrigin;
  }
//******************************************************************************
  CAttributePtr& CSetBrushSource::NewDestinationSize(){
    return this->pvNewDestinationSize;
  }
//******************************************************************************
  const CAttributePtr& CSetBrushSource::NewDestinationSize() const{
    return this->pvNewDestinationSize;
  }

}; /* namespace pcl6 */
