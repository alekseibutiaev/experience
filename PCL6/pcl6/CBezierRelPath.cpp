//*****************************************************************************
//        File: CBezierRelPath.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBezierRelPath.hpp"

namespace pcl6 {

//******************************************************************************
  CBezierRelPath::CBezierRelPath() : CPclOperator( PclTag::eBezierRelPath ),
    pvNumberOfPoints( CreateAttribute< Attribute::eNumberOfPoints >( AttributeIs::Obligatory ) ),
    pvPointType( CreateAttribute< Attribute::ePointType >( AttributeIs::Obligatory ) ),
    pvControlPoint1( CreateAttribute< Attribute::eControlPoint1 >( AttributeIs::Obligatory ) ),
    pvControlPoint2( CreateAttribute< Attribute::eControlPoint2 >( AttributeIs::Obligatory ) ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBezierRelPath::~CBezierRelPath() {
  }
//******************************************************************************
  bool CBezierRelPath::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvNumberOfPoints,
        &pvPointType,
        &pvControlPoint1,
        &pvControlPoint2,
        &pvEndPoint,
        0L );
  }
//******************************************************************************
  bool CBezierRelPath::IsValid() const{
    return ( pvNumberOfPoints->IsValid() && pvPointType->IsValid() ) ||
      ( pvControlPoint2->IsValid() && pvEndPoint->IsValid() &&
        pvControlPoint1->IsValid() );
  }
//******************************************************************************
  CAttributePtr& CBezierRelPath::NumberOfPoints(){
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  const CAttributePtr& CBezierRelPath::NumberOfPoints() const{
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  CAttributePtr& CBezierRelPath::PointType(){
    return this->pvPointType;
  }
//******************************************************************************
  const CAttributePtr& CBezierRelPath::PointType() const {
    return this->pvPointType;
  }
//******************************************************************************
  CAttributePtr& CBezierRelPath::ControlPoint1(){
    return this->pvControlPoint1;
  }
//******************************************************************************
  const CAttributePtr& CBezierRelPath::ControlPoint1()  const{
    return this->pvControlPoint1;
  }
//******************************************************************************
  CAttributePtr& CBezierRelPath::ControlPoint2(){
    return this->pvControlPoint2;
  }
//******************************************************************************
  const CAttributePtr& CBezierRelPath::ControlPoint2() const{
    return this->pvControlPoint2;
  }
//******************************************************************************
  CAttributePtr& CBezierRelPath::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CBezierRelPath::EndPoint() const{
    return this->pvEndPoint;
  }

}; /* namespace pcl6 */
