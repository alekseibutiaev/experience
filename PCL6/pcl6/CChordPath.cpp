//*****************************************************************************
//        File: CChordPath.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CChordPath.hpp"

namespace pcl6 {

//******************************************************************************
  CChordPath::CChordPath() : CPclOperator( PclTag::eChordPath ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) ),
    pvStartPoint( CreateAttribute< Attribute::eStartPoint >( AttributeIs::Obligatory ) ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CChordPath::~CChordPath() {
  }
//******************************************************************************
  bool CChordPath::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        &pvStartPoint,
        &pvEndPoint,
        0L );
  }
//******************************************************************************
  bool CChordPath::IsValid() const{
    return pvBoundingBox->IsValid() && pvStartPoint->IsValid() &&
      pvEndPoint->IsValid();
  }
//******************************************************************************
  CAttributePtr& CChordPath::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CChordPath::BoundingBox() const{
    return this->pvBoundingBox;
  }
//******************************************************************************
  CAttributePtr& CChordPath::StartPoint(){
    return this->pvStartPoint;
  }
//******************************************************************************
  const CAttributePtr& CChordPath::StartPoint() const {
    return this->pvStartPoint;
  }
//******************************************************************************
  CAttributePtr& CChordPath::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CChordPath::EndPoint()  const{
    return this->pvEndPoint;
  }

}; /* namespace pcl6 */
