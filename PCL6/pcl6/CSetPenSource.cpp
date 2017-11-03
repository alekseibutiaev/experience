//*****************************************************************************
//        File: CSetPenSource.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetPenSource.hpp"

namespace pcl6 {

//******************************************************************************
  CSetPenSource::CSetPenSource() : CPclOperator( PclTag::eSetPenSource ),
    pvRGBColor( CreateAttribute< Attribute::eRGBColor >( AttributeIs::Obligatory ) ),
    pvGrayLevel( CreateAttribute< Attribute::eGrayLevel >( AttributeIs::Obligatory ) ),
    pvNullPen( CreateAttribute< Attribute::eNullPen >( AttributeIs::Obligatory ) ),
    pvPrimaryArray( CreateAttribute< Attribute::ePrimaryArray >( AttributeIs::Obligatory ) ),
    pvPrimaryDepth( CreateAttribute< Attribute::ePrimaryDepth >( AttributeIs::Obligatory ) ),
    pvPatternSelectID( CreateAttribute< Attribute::ePatternSelectID >( AttributeIs::Obligatory ) ),
    pvPatternOrigin( CreateAttribute< Attribute::ePatternOrigin >( AttributeIs::Optional ) ),
    pvNewDestinationSize( CreateAttribute< Attribute::eNewDestinationSize >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetPenSource::~CSetPenSource() {
  }
//******************************************************************************
  bool CSetPenSource::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvRGBColor,
        &pvGrayLevel,
        &pvNullPen,
        &pvPrimaryArray,
        &pvPrimaryDepth,
        &pvPatternSelectID,
        &pvPatternOrigin,
        &pvNewDestinationSize,
        0L );
  }
//******************************************************************************
  bool CSetPenSource::IsValid() const{
    return pvRGBColor->IsValid() || pvGrayLevel->IsValid() ||
      ( pvPrimaryArray->IsValid() && pvPrimaryDepth->IsValid() ) ||
        pvNullPen->IsValid() ||
        ( pvPatternSelectID->IsValid() &&
            ( pvPatternOrigin->IsValid() && pvNewDestinationSize->IsValid() ) );
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::RGBColor(){
    return this->pvRGBColor;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::RGBColor() const{
    return this->pvRGBColor;
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::GrayLevel(){
    return this->pvGrayLevel;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::GrayLevel() const {
    return this->pvGrayLevel;
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::NullPen(){
    return this->pvNullPen;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::NullPen()  const{
    return this->pvNullPen;
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::PrimaryArray(){
    return this->pvPrimaryArray;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::PrimaryArray() const{
    return this->pvPrimaryArray;
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::PrimaryDepth(){
    return this->pvPrimaryDepth;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::PrimaryDepth() const{
    return this->pvPrimaryDepth;
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::PatternSelectID(){
    return this->pvPatternSelectID;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::PatternSelectID() const{
    return this->pvPatternSelectID;
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::PatternOrigin(){
    return this->pvPatternOrigin;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::PatternOrigin() const{
    return this->pvPatternOrigin;
  }
//******************************************************************************
  CAttributePtr& CSetPenSource::NewDestinationSize(){
    return this->pvNewDestinationSize;
  }
//******************************************************************************
  const CAttributePtr& CSetPenSource::NewDestinationSize() const{
    return this->pvNewDestinationSize;
  }

}; /* namespace pcl6 */
