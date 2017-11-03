//*****************************************************************************
//        File: CExecStream.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CExecStream.hpp"

namespace pcl6 {
//******************************************************************************
  CExecStream::CExecStream() : CPclOperator( PclTag::eExecStream ),
    pvStreamName( CreateAttribute< Attribute::eStreamName >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CExecStream::~CExecStream() {
  }
//******************************************************************************
  bool CExecStream::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvStreamName,
        0L );
  }
//******************************************************************************
  bool CExecStream::IsValid() const{
    return pvStreamName->IsValid();
  }
//******************************************************************************
  CAttributePtr& CExecStream::StreamName(){
    return this->pvStreamName;
  }
//******************************************************************************
  const CAttributePtr& CExecStream::StreamName() const{
    return this->pvStreamName;
  }

}
