//*****************************************************************************
//        File: CBezierPath.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBezierPath.hpp"

namespace pcl6 {

//******************************************************************************
  CBezierPath::CBezierPath() : CPclOperator( PclTag::eBezierPath ),
    pvNumberOfPoints( CreateAttribute< Attribute::eNumberOfPoints >( AttributeIs::Obligatory ) ),
    pvPointType( CreateAttribute< Attribute::ePointType >( AttributeIs::Obligatory ) ),
    pvControlPoint1( CreateAttribute< Attribute::eControlPoint1 >( AttributeIs::Obligatory ) ),
    pvControlPoint2( CreateAttribute< Attribute::eControlPoint2 >( AttributeIs::Obligatory ) ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBezierPath::~CBezierPath() {
  }
//******************************************************************************
  bool CBezierPath::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvNumberOfPoints,
        &pvPointType,
        &pvControlPoint1,
        &pvControlPoint2,
        &pvEndPoint,
        0L );
  }
//******************************************************************************
  bool CBezierPath::IsValid() const{
    return ( pvNumberOfPoints->IsValid() && pvPointType->IsValid() ) ||
      ( pvControlPoint2->IsValid() && pvEndPoint->IsValid() &&
        pvControlPoint1->IsValid() );
  }
//******************************************************************************
  CAttributePtr& CBezierPath::NumberOfPoints(){
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  const CAttributePtr& CBezierPath::NumberOfPoints() const{
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  CAttributePtr& CBezierPath::PointType(){
    return this->pvPointType;
  }
//******************************************************************************
  const CAttributePtr& CBezierPath::PointType() const {
    return this->pvPointType;
  }
//******************************************************************************
  CAttributePtr& CBezierPath::ControlPoint1(){
    return this->pvControlPoint1;
  }
//******************************************************************************
  const CAttributePtr& CBezierPath::ControlPoint1()  const{
    return this->pvControlPoint1;
  }
//******************************************************************************
  CAttributePtr& CBezierPath::ControlPoint2(){
    return this->pvControlPoint2;
  }
//******************************************************************************
  const CAttributePtr& CBezierPath::ControlPoint2() const{
    return this->pvControlPoint2;
  }
//******************************************************************************
  CAttributePtr& CBezierPath::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CBezierPath::EndPoint() const{
    return this->pvEndPoint;
  }

}; /* namespace pcl6 */
