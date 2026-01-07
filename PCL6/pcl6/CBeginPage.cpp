//*****************************************************************************
//        File: CBeginPage.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBeginPage.hpp"

namespace pcl6 {

//******************************************************************************
  CBeginPage::CBeginPage() : CPclOperator( PclTag::eBeginPage ),
    pvOrientation( CreateAttribute< Attribute::eOrientation >( AttributeIs::Optional ) ),
    pvMediaSource( CreateAttribute< Attribute::eMediaSource >( AttributeIs::Optional ) ),
    pvMediaSize( CreateAttribute< Attribute::eMediaSize >( AttributeIs::Optional ) ),
    pvCustomMediaSize( CreateAttribute< Attribute::eCustomMediaSize >( AttributeIs::Obligatory ) ),
    pvCustomMediaSizeUnits( CreateAttribute< Attribute::eCustomMediaSizeUnits >( AttributeIs::Obligatory ) ),
    pvMediaType( CreateAttribute< Attribute::eMediaType >( AttributeIs::Optional ) ),
    pvMediaDestination( CreateAttribute< Attribute::eMediaDestination >( AttributeIs::Optional ) ),
    pvSimplexPageMode( CreateAttribute< Attribute::eSimplexPageMode >( AttributeIs::Optional ) ),
    pvDuplexPageMode( CreateAttribute< Attribute::eDuplexPageMode >( AttributeIs::Optional ) ),
    pvDuplexPageSide( CreateAttribute< Attribute::eDuplexPageSide >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBeginPage::~CBeginPage() {
  }
//******************************************************************************
  bool CBeginPage::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvOrientation,
        &pvMediaSource,
        &pvMediaSize,
        &pvCustomMediaSize,
        &pvCustomMediaSizeUnits,
        &pvMediaType,
        &pvMediaDestination,
        &pvSimplexPageMode,
        &pvDuplexPageMode,
        &pvDuplexPageSide,
        0L );
  }
//******************************************************************************
    bool CBeginPage::IsValid() const{
//      bool a = pvCustomMediaSize->IsValid() && pvCustomMediaSizeUnits->IsValid();
//      bool b = pvDuplexPageMode->IsValid() && DuplexPageSide->IsValid();
      return pvOrientation->IsValid() && pvMediaType->IsValid() &&
        pvMediaSource->IsValid() && pvMediaDestination->IsValid();
  #if 0
      Orientation opt &
      { MediaSize opt | {CustomMediaSize & CustomMediaSizeUnits} opt } &
      MediaType opt &
      MediaSource opt &
      MediaDestination opt &
      { SimplexPageMode opt | {DuplexPageMode opt & {DuplexPageSide opt } }

  #endif
      return false;
    }
//******************************************************************************
  CAttributePtr& CBeginPage::Orientation(){
    return pvOrientation;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::Orientation() const{
    return pvOrientation;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::MediaSource(){
    return pvMediaSource;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::MediaSource()  const{
    return pvMediaSource;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::MediaSize(){
    return pvMediaSize;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::MediaSize() const{
    return pvMediaSize;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::CustomMediaSize(){
    return pvCustomMediaSize;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::CustomMediaSize() const{
    return pvCustomMediaSize;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::CustomMediaSizeUnits(){
    return pvCustomMediaSizeUnits;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::CustomMediaSizeUnits() const{
    return pvCustomMediaSizeUnits;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::MediaType(){
    return pvMediaType;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::MediaType() const{
    return pvMediaType;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::MediaDestination(){
    return pvMediaDestination;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::MediaDestination() const{
    return pvMediaDestination;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::SimplexPageMode(){
    return pvSimplexPageMode;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::SimplexPageMode() const{
    return pvSimplexPageMode;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::DuplexPageMode(){
    return pvDuplexPageMode;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::DuplexPageMode() const{
    return pvDuplexPageMode;
  }
//******************************************************************************
  CAttributePtr& CBeginPage::DuplexPageSide(){
    return pvDuplexPageSide;
  }
//******************************************************************************
  const CAttributePtr& CBeginPage::DuplexPageSide() const{
    return pvDuplexPageSide;
  }

}
