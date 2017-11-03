//*****************************************************************************
//        File: CRectanglePath.cpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CRectanglePath.hpp"

namespace pcl6 {
//******************************************************************************
  CRectanglePath::CRectanglePath() : CPclOperator( PclTag::eRectanglePath ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CRectanglePath::~CRectanglePath() {
  }
//******************************************************************************
  bool CRectanglePath::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        0L );
  }
//******************************************************************************
  bool CRectanglePath::IsValid() const{
    return pvBoundingBox->IsValid();
  }
//******************************************************************************
  CAttributePtr& CRectanglePath::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CRectanglePath::BoundingBox() const{
    return this->pvBoundingBox;
  }

}
