//*****************************************************************************
//        File: CPiePath.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CPiePath.hpp"

namespace pcl6 {

//******************************************************************************
  CPiePath::CPiePath() : CPclOperator( PclTag::ePiePath ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) ),
    pvStartPoint( CreateAttribute< Attribute::eStartPoint >( AttributeIs::Obligatory ) ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CPiePath::~CPiePath() {
  }
//******************************************************************************
  bool CPiePath::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        &pvStartPoint,
        &pvEndPoint,
        0L );
  }
//******************************************************************************
  bool CPiePath::IsValid() const{
    return pvBoundingBox->IsValid() && pvStartPoint->IsValid() &&
      pvEndPoint->IsValid();
  }
//******************************************************************************
  CAttributePtr& CPiePath::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CPiePath::BoundingBox() const{
    return this->pvBoundingBox;
  }
//******************************************************************************
  CAttributePtr& CPiePath::StartPoint(){
    return this->pvStartPoint;
  }
//******************************************************************************
  const CAttributePtr& CPiePath::StartPoint() const {
    return this->pvStartPoint;
  }
//******************************************************************************
  CAttributePtr& CPiePath::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CPiePath::EndPoint()  const{
    return this->pvEndPoint;
  }

}; /* namespace pcl6 */
