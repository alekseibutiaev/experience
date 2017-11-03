//*****************************************************************************
//        File: CLinePath.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CLinePath.hpp"

namespace pcl6 {

//******************************************************************************
  CLinePath::CLinePath() : CPclOperator( PclTag::eLinePath ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) ),
    pvNumberOfPoints( CreateAttribute< Attribute::eNumberOfPoints >( AttributeIs::Obligatory ) ),
    pvPointType( CreateAttribute< Attribute::ePointType >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CLinePath::~CLinePath() {
  }
//******************************************************************************
  bool CLinePath::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvEndPoint,
        &pvNumberOfPoints,
        &pvPointType,
        0L );
  }
//******************************************************************************
  bool CLinePath::IsValid() const{
    return pvEndPoint->IsValid() || ( pvNumberOfPoints->IsValid() &&
      pvPointType->IsValid() );
  }
//******************************************************************************
  CAttributePtr& CLinePath::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CLinePath::EndPoint() const{
    return this->pvEndPoint;
  }
//******************************************************************************
  CAttributePtr& CLinePath::NumberOfPoints(){
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  const CAttributePtr& CLinePath::NumberOfPoints() const {
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  CAttributePtr& CLinePath::PointType(){
    return this->pvPointType;
  }
//******************************************************************************
  const CAttributePtr& CLinePath::PointType()  const{
    return this->pvPointType;
  }

}; /* namespace pcl6 */
