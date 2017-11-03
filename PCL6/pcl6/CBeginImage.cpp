//*****************************************************************************
//        File: CBeginImage.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBeginImage.hpp"

namespace pcl6 {

//******************************************************************************
  CBeginImage::CBeginImage() : CPclOperator( PclTag::eBeginImage ),
    pvColorDepth( CreateAttribute< Attribute::eColorDepth >( AttributeIs::Obligatory ) ),
    pvColorMapping( CreateAttribute< Attribute::eColorMapping >( AttributeIs::Obligatory ) ),
    pvDestinationSize( CreateAttribute< Attribute::eDestinationSize >( AttributeIs::Obligatory ) ),
    pvSourceWidth( CreateAttribute< Attribute::eSourceWidth >( AttributeIs::Obligatory ) ),
    pvSourceHeight( CreateAttribute< Attribute::eSourceHeight >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBeginImage::~CBeginImage() {
  }
//******************************************************************************
  bool CBeginImage::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvColorDepth,
        &pvColorMapping,
        &pvDestinationSize,
        &pvSourceWidth,
        &pvSourceHeight,
        0L );
  }
//******************************************************************************
  bool CBeginImage::IsValid() const{
    return pvColorDepth->IsValid() && pvColorMapping->IsValid() &&
      pvSourceWidth->IsValid() && pvSourceHeight->IsValid() &&
        pvDestinationSize->IsValid();
  }
//******************************************************************************
  CAttributePtr& CBeginImage::ColorDepth(){
    return this->pvColorDepth;
  }
//******************************************************************************
  const CAttributePtr& CBeginImage::ColorDepth() const{
    return this->pvColorDepth;
  }
//******************************************************************************
  CAttributePtr& CBeginImage::ColorMapping(){
    return this->pvColorMapping;
  }
//******************************************************************************
  const CAttributePtr& CBeginImage::ColorMapping() const {
    return this->pvColorMapping;
  }
//******************************************************************************
  CAttributePtr& CBeginImage::DestinationSize(){
    return this->pvDestinationSize;
  }
//******************************************************************************
  const CAttributePtr& CBeginImage::DestinationSize()  const{
    return this->pvDestinationSize;
  }
//******************************************************************************
  CAttributePtr& CBeginImage::SourceWidth(){
    return this->pvSourceWidth;
  }
//******************************************************************************
  const CAttributePtr& CBeginImage::SourceWidth() const{
    return this->pvSourceWidth;
  }
//******************************************************************************
  CAttributePtr& CBeginImage::SourceHeight(){
    return this->pvSourceHeight;
  }
//******************************************************************************
  const CAttributePtr& CBeginImage::SourceHeight() const{
    return this->pvSourceHeight;
  }

}; /* namespace pcl6 */
