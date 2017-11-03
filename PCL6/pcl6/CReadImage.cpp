//*****************************************************************************
//        File: CReadImage.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CReadImage.hpp"

namespace pcl6 {

//******************************************************************************
  CReadImage::CReadImage() : CPclOperator( PclTag::eReadImage ),
    pvCompressMode( CreateAttribute< Attribute::eCompressMode >( AttributeIs::Obligatory ) ),
    pvStartLine( CreateAttribute< Attribute::eStartLine >( AttributeIs::Obligatory ) ),
    pvBlockHeight( CreateAttribute< Attribute::eBlockHeight >( AttributeIs::Obligatory ) ),
    pvPadBytesMultiple( CreateAttribute< Attribute::ePadBytesMultiple >( AttributeIs::Optional ) ),
    pvBlockByteLength( CreateAttribute< Attribute::eBlockByteLength >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CReadImage::~CReadImage() {
  }
//******************************************************************************
  bool CReadImage::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvCompressMode,
        &pvStartLine,
        &pvBlockHeight,
        &pvPadBytesMultiple,
        &pvBlockByteLength,
        0L );
  }
//******************************************************************************
  bool CReadImage::IsValid() const{
    return pvCompressMode->IsValid() && pvStartLine->IsValid() &&
      pvPadBytesMultiple->IsValid() && pvBlockByteLength->IsValid() &&
        pvBlockHeight->IsValid();
  }
//******************************************************************************
  CAttributePtr& CReadImage::CompressMode(){
    return this->pvCompressMode;
  }
//******************************************************************************
  const CAttributePtr& CReadImage::CompressMode() const{
    return this->pvCompressMode;
  }
//******************************************************************************
  CAttributePtr& CReadImage::StartLine(){
    return this->pvStartLine;
  }
//******************************************************************************
  const CAttributePtr& CReadImage::StartLine() const {
    return this->pvStartLine;
  }
//******************************************************************************
  CAttributePtr& CReadImage::BlockHeight(){
    return this->pvBlockHeight;
  }
//******************************************************************************
  const CAttributePtr& CReadImage::BlockHeight()  const{
    return this->pvBlockHeight;
  }
//******************************************************************************
  CAttributePtr& CReadImage::PadBytesMultiple(){
    return this->pvPadBytesMultiple;
  }
//******************************************************************************
  const CAttributePtr& CReadImage::PadBytesMultiple() const{
    return this->pvPadBytesMultiple;
  }
//******************************************************************************
  CAttributePtr& CReadImage::BlockByteLength(){
    return this->pvBlockByteLength;
  }
//******************************************************************************
  const CAttributePtr& CReadImage::BlockByteLength() const{
    return this->pvBlockByteLength;
  }
}; /* namespace pcl6 */
