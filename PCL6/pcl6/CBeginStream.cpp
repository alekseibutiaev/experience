//*****************************************************************************
//        File: CBeginStream.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBeginStream.hpp"

namespace pcl6 {
//******************************************************************************
  CBeginStream::CBeginStream() : CPclOperator( PclTag::eBeginStream ),
    pvStreamName( CreateAttribute< Attribute::eStreamName >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBeginStream::~CBeginStream() {
  }
//******************************************************************************
  bool CBeginStream::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvStreamName,
        0L );
  }
//******************************************************************************
  bool CBeginStream::IsValid() const{
    return pvStreamName->IsValid();
  }
//******************************************************************************
  CAttributePtr& CBeginStream::StreamName(){
    return this->pvStreamName;
  }
//******************************************************************************
  const CAttributePtr& CBeginStream::StreamName() const{
    return this->pvStreamName;
  }

}
