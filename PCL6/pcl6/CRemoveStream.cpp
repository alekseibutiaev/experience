//*****************************************************************************
//        File: CRemoveStream.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CRemoveStream.hpp"

namespace pcl6 {
//******************************************************************************
  CRemoveStream::CRemoveStream() : CPclOperator( PclTag::eRemoveStream ),
    pvStreamName( CreateAttribute< Attribute::eStreamName >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CRemoveStream::~CRemoveStream() {
  }
//******************************************************************************
  bool CRemoveStream::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvStreamName,
        0L );
  }
//******************************************************************************
  bool CRemoveStream::IsValid() const{
    return pvStreamName->IsValid();
  }
//******************************************************************************
  CAttributePtr& CRemoveStream::StreamName(){
    return this->pvStreamName;
  }
//******************************************************************************
  const CAttributePtr& CRemoveStream::StreamName() const{
    return this->pvStreamName;
  }

}
