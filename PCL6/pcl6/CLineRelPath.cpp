//*****************************************************************************
//        File: CLineRelPath.hpp
//     Project: kopirkin
//  Created on: 28.11.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CLineRelPath.hpp"

namespace pcl6 {

//******************************************************************************
  CLineRelPath::CLineRelPath() : CPclOperator( PclTag::eLineRelPath ),
    pvEndPoint( CreateAttribute< Attribute::eEndPoint >( AttributeIs::Obligatory ) ),
    pvNumberOfPoints( CreateAttribute< Attribute::eNumberOfPoints >( AttributeIs::Obligatory ) ),
    pvPointType( CreateAttribute< Attribute::ePointType >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CLineRelPath::~CLineRelPath() {
  }
//******************************************************************************
  bool CLineRelPath::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvEndPoint,
        &pvNumberOfPoints,
        &pvPointType,
        0L );
  }
//******************************************************************************
  bool CLineRelPath::IsValid() const{
    return pvEndPoint->IsValid() ||
      ( pvNumberOfPoints->IsValid() && pvPointType->IsValid() );
  }
//******************************************************************************
  CAttributePtr& CLineRelPath::EndPoint(){
    return this->pvEndPoint;
  }
//******************************************************************************
  const CAttributePtr& CLineRelPath::EndPoint() const{
    return this->pvEndPoint;
  }
//******************************************************************************
  CAttributePtr& CLineRelPath::NumberOfPoints(){
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  const CAttributePtr& CLineRelPath::NumberOfPoints() const {
    return this->pvNumberOfPoints;
  }
//******************************************************************************
  CAttributePtr& CLineRelPath::PointType(){
    return this->pvPointType;
  }
//******************************************************************************
  const CAttributePtr& CLineRelPath::PointType()  const{
    return this->pvPointType;
  }

}; /* namespace pcl6 */
