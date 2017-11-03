//*****************************************************************************
//        File: CReadStream.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CReadStream.hpp"

namespace pcl6 {
//******************************************************************************
  CReadStream::CReadStream() : CPclOperator( PclTag::eReadStream ),
    pvStreamDataLength( CreateAttribute< Attribute::eStreamDataLength >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CReadStream::~CReadStream() {
  }
//******************************************************************************
  bool CReadStream::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvStreamDataLength,
        0L );
  }
//******************************************************************************
  bool CReadStream::IsValid() const{
    return pvStreamDataLength->IsValid();
  }
//******************************************************************************
  CAttributePtr& CReadStream::StreamDataLength(){
    return this->pvStreamDataLength;
  }
//******************************************************************************
  const CAttributePtr& CReadStream::StreamDataLength() const{
    return this->pvStreamDataLength;
  }

}
