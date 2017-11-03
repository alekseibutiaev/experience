//*****************************************************************************
//        File: CReadRastPattern.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CReadRastPattern.hpp"

namespace pcl6 {

//  multiAttributeList ::= { CompressMode & StartLine & BlockHeight
//                              & {PadBytesMultiple}opt & {BlockByteLength}opt}


//******************************************************************************
  CReadRastPattern::CReadRastPattern() : CPclOperator( PclTag::eReadRastPattern ),
    pvCompressMode( CreateAttribute< Attribute::eCompressMode >( AttributeIs::Obligatory ) ),
    pvStartLine( CreateAttribute< Attribute::eStartLine >( AttributeIs::Obligatory ) ),
    pvBlockHeight( CreateAttribute< Attribute::eBlockHeight >( AttributeIs::Obligatory ) ),
    pvPadBytesMultiple( CreateAttribute< Attribute::ePadBytesMultiple >( AttributeIs::Optional ) ),
    pvBlockByteLength( CreateAttribute< Attribute::eBlockByteLength >( AttributeIs::Optional ) ) {
    OPERATOR_NAME;
  }
//******************************************************************************
  CReadRastPattern::~CReadRastPattern() {
  }
//******************************************************************************
  bool CReadRastPattern::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvCompressMode,
        &pvStartLine,
        &pvBlockHeight,
        &pvPadBytesMultiple,
        &pvBlockByteLength,
        0L );
  }
//******************************************************************************
  bool CReadRastPattern::IsValid() const{
    return pvCompressMode->IsValid() && pvStartLine->IsValid() &&
        pvBlockHeight->IsValid() && pvPadBytesMultiple->IsValid() &&
        pvBlockByteLength->IsValid();
  }
//******************************************************************************
  CAttributePtr& CReadRastPattern::CompressMode(){
    return this->pvCompressMode;
  }
//******************************************************************************
  const CAttributePtr& CReadRastPattern::CompressMode() const{
    return this->pvCompressMode;
  }
//******************************************************************************
  CAttributePtr& CReadRastPattern::StartLine(){
    return this->pvStartLine;
  }
//******************************************************************************
  const CAttributePtr& CReadRastPattern::StartLine() const {
    return this->pvStartLine;
  }
//******************************************************************************
  CAttributePtr& CReadRastPattern::BlockHeight(){
    return this->pvBlockHeight;
  }
//******************************************************************************
  const CAttributePtr& CReadRastPattern::BlockHeight()  const{
    return this->pvBlockHeight;
  }
//******************************************************************************
  CAttributePtr& CReadRastPattern::PadBytesMultiple(){
    return this->pvPadBytesMultiple;
  }
//******************************************************************************
  const CAttributePtr& CReadRastPattern::PadBytesMultiple() const{
    return this->pvPadBytesMultiple;
  }
//******************************************************************************
  CAttributePtr& CReadRastPattern::BlockByteLength(){
    return this->pvBlockByteLength;
  }
//******************************************************************************
  const CAttributePtr& CReadRastPattern::BlockByteLength() const{
    return this->pvBlockByteLength;
  }

}; /* namespace pcl6 */
