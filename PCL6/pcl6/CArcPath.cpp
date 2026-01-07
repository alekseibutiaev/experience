//*****************************************************************************
//        File: CArcPath.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CArcPath.hpp"

namespace pcl6 {

//******************************************************************************
  CArcPath::CArcPath() : CPclOperator( PclTag::eArcPath ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) ),
    pvStartPoint( CreateAttribute< Attribute::eStartPoint >( AttributeIs::Obligatory ) ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) ),
    pvArcDirection( CreateAttribute< Attribute::eArcDirection >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CArcPath::~CArcPath() {
  }
//******************************************************************************
  bool CArcPath::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        &pvStartPoint,
        &pvEndPoint,
        &pvArcDirection,
        0L );
  }
//******************************************************************************
  bool CArcPath::IsValid() const{
    return pvBoundingBox->IsValid() && pvStartPoint->IsValid() &&
    pvEndPoint->IsValid() && pvArcDirection->IsValid();
  }
//******************************************************************************
  CAttributePtr& CArcPath::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CArcPath::BoundingBox() const{
    return this->pvBoundingBox;
  }
//******************************************************************************
  CAttributePtr& CArcPath::StartPoint(){
    return this->pvStartPoint;
  }
//******************************************************************************
  const CAttributePtr& CArcPath::StartPoint() const {
    return this->pvStartPoint;
  }
//******************************************************************************
  CAttributePtr& CArcPath::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CArcPath::EndPoint()  const{
    return this->pvEndPoint;
  }
//******************************************************************************
  CAttributePtr& CArcPath::ArcDirection(){
    return this->pvArcDirection;
  }
//******************************************************************************
  const CAttributePtr& CArcPath::ArcDirection() const{
    return this->pvArcDirection;
  }

}; /* namespace pcl6 */
