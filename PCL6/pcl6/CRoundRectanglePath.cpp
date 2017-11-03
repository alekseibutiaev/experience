//*****************************************************************************
//        File: CRoundRectanglePath.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CRoundRectanglePath.hpp"

namespace pcl6 {

//******************************************************************************
  CRoundRectanglePath::CRoundRectanglePath() : CPclOperator( PclTag::eRoundRectanglePath ),
    pvEllipseDimension( CreateAttribute< Attribute::eEllipseDimension >( AttributeIs::Obligatory ) ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CRoundRectanglePath::~CRoundRectanglePath() {
  }
//******************************************************************************
  bool CRoundRectanglePath::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvEllipseDimension,
        &pvBoundingBox,
        0L );
  }
//******************************************************************************
  bool CRoundRectanglePath::IsValid() const{
    return pvEllipseDimension->IsValid() && pvBoundingBox->IsValid();
  }
//******************************************************************************
  CAttributePtr& CRoundRectanglePath::EllipseDimension(){
    return this->pvEllipseDimension;
  }
//******************************************************************************
  const CAttributePtr& CRoundRectanglePath::EllipseDimension() const{
    return this->pvEllipseDimension;
  }
//******************************************************************************
  CAttributePtr& CRoundRectanglePath::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CRoundRectanglePath::BoundingBox() const {
    return this->pvBoundingBox;
  }

}; /* namespace pcl6 */
