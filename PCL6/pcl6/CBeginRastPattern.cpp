//*****************************************************************************
//        File: CBeginRastPattern.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBeginRastPattern.hpp"

namespace pcl6 {

//******************************************************************************
  CBeginRastPattern::CBeginRastPattern() : CPclOperator( PclTag::eBeginRastPattern ),
    pvColorDepth( CreateAttribute< Attribute::eColorMapping >( AttributeIs::Obligatory ) ),
    pvColorMapping( CreateAttribute< Attribute::eColorMapping >( AttributeIs::Obligatory ) ),
    pvDestinationSize( CreateAttribute< Attribute::eDestinationSize >( AttributeIs::Obligatory ) ),
    pvSourceWidth( CreateAttribute< Attribute::eSourceWidth >( AttributeIs::Obligatory ) ),
    pvSourceHeight( CreateAttribute< Attribute::eSourceHeight >( AttributeIs::Obligatory ) ),
    pvPatternDefineID( CreateAttribute< Attribute::ePatternDefineID >( AttributeIs::Obligatory ) ),
    pvPatternPersistence( CreateAttribute< Attribute::ePatternPersistence >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBeginRastPattern::~CBeginRastPattern() {
  }
//******************************************************************************
  bool CBeginRastPattern::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvColorDepth,
        &pvColorMapping,
        &pvDestinationSize,
        &pvSourceWidth,
        &pvSourceHeight,
        &pvPatternDefineID,
        &pvPatternPersistence,
        0L );
  }
//******************************************************************************
  bool CBeginRastPattern::IsValid() const{
    return pvColorDepth->IsValid() && pvColorMapping->IsValid() &&
        pvSourceWidth->IsValid() && pvSourceHeight->IsValid() &&
        pvDestinationSize->IsValid() && pvPatternDefineID->IsValid() &&
          pvPatternPersistence->IsValid();
  }
//******************************************************************************
  CAttributePtr& CBeginRastPattern::ColorDepth(){
    return this->pvColorDepth;
  }
//******************************************************************************
  const CAttributePtr& CBeginRastPattern::ColorDepth() const{
    return this->pvColorDepth;
  }
//******************************************************************************
  CAttributePtr& CBeginRastPattern::ColorMapping(){
    return this->pvColorMapping;
  }
//******************************************************************************
  const CAttributePtr& CBeginRastPattern::ColorMapping() const {
    return this->pvColorMapping;
  }
//******************************************************************************
  CAttributePtr& CBeginRastPattern::DestinationSize(){
    return this->pvDestinationSize;
  }
//******************************************************************************
  const CAttributePtr& CBeginRastPattern::DestinationSize()  const{
    return this->pvDestinationSize;
  }
//******************************************************************************
  CAttributePtr& CBeginRastPattern::SourceWidth(){
    return this->pvSourceWidth;
  }
//******************************************************************************
  const CAttributePtr& CBeginRastPattern::SourceWidth() const{
    return this->pvSourceWidth;
  }
//******************************************************************************
  CAttributePtr& CBeginRastPattern::SourceHeight(){
    return this->pvSourceHeight;
  }
//******************************************************************************
  const CAttributePtr& CBeginRastPattern::SourceHeight() const{
    return this->pvSourceHeight;
  }
//******************************************************************************
  CAttributePtr& CBeginRastPattern::PatternDefineID(){
    return this->pvPatternDefineID;
  }
//******************************************************************************
  const CAttributePtr& CBeginRastPattern::PatternDefineID() const{
    return this->pvPatternDefineID;
  }
//******************************************************************************
  CAttributePtr& CBeginRastPattern::PatternPersistence(){
    return this->pvPatternPersistence;
  }
//******************************************************************************
  const CAttributePtr& CBeginRastPattern::PatternPersistence() const{
    return this->pvPatternPersistence;
  }

}; /* namespace pcl6 */
