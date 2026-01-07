//*****************************************************************************
//        File: CPie.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CPie.hpp"

namespace pcl6 {

//******************************************************************************
  CPie::CPie() : CPclOperator( PclTag::ePie ),
    pvBoundingBox( CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Obligatory ) ),
    pvStartPoint( CreateAttribute< Attribute::eStartPoint >( AttributeIs::Obligatory ) ),
    pvErrorReport( CreateAttribute< Attribute::eErrorReport >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CPie::~CPie() {
  }
//******************************************************************************
  bool CPie::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvBoundingBox,
        &pvStartPoint,
        &pvErrorReport,
        0L );
  }
//******************************************************************************
  bool CPie::IsValid() const{
    return pvBoundingBox->IsValid() && pvStartPoint->IsValid() &&
      pvErrorReport->IsValid();
  }
//******************************************************************************
  CAttributePtr& CPie::BoundingBox(){
    return this->pvBoundingBox;
  }
//******************************************************************************
  const CAttributePtr& CPie::BoundingBox() const{
    return this->pvBoundingBox;
  }
//******************************************************************************
  CAttributePtr& CPie::StartPoint(){
    return this->pvStartPoint;
  }
//******************************************************************************
  const CAttributePtr& CPie::StartPoint() const {
    return this->pvStartPoint;
  }
//******************************************************************************
  CAttributePtr& CPie::ErrorReport(){
    return this->pvErrorReport;
  }
//******************************************************************************
  const CAttributePtr& CPie::ErrorReport()  const{
    return this->pvErrorReport;
  }

}; /* namespace pcl6 */
