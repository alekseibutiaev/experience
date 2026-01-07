//*****************************************************************************
//        File: CChord.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CChord.hpp"

namespace pcl6 {

//******************************************************************************
  CChord::CChord() : CPclOperator( PclTag::eChord ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) ),
    pvStartPoint( CreateAttribute< Attribute::eStartPoint >( AttributeIs::Obligatory ) ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CChord::~CChord() {
  }
//******************************************************************************
  bool CChord::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        &pvStartPoint,
        &pvEndPoint,
        0L );
  }
//******************************************************************************
  bool CChord::IsValid() const{
    return pvBoundingBox->IsValid() && pvStartPoint->IsValid() &&
      pvEndPoint->IsValid();
  }
//******************************************************************************
  CAttributePtr& CChord::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CChord::BoundingBox() const{
    return this->pvBoundingBox;
  }
//******************************************************************************
  CAttributePtr& CChord::StartPoint(){
    return this->pvStartPoint;
  }
//******************************************************************************
  const CAttributePtr& CChord::StartPoint() const {
    return this->pvStartPoint;
  }
//******************************************************************************
  CAttributePtr& CChord::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CChord::EndPoint()  const{
    return this->pvEndPoint;
  }

}; /* namespace pcl6 */
