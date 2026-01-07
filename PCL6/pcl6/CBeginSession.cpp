//*****************************************************************************
//        File: CBeginSession.cpp
//     Project: kopirkin
//  Created on: 28.11.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CBeginSession.hpp"

namespace pcl6 {

//******************************************************************************
  CBeginSession::CBeginSession() : CPclOperator( PclTag::eBeginSession ),
    pvMeasure( CreateAttribute< Attribute::eMeasure >( AttributeIs::Obligatory ) ),
    pvUnitsPerMeasure( CreateAttribute< Attribute::eUnitsPerMeasure >( AttributeIs::Obligatory ) ),
    pvErrorReport( CreateAttribute< Attribute::eErrorReport >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CBeginSession::~CBeginSession() {
  }
//******************************************************************************
  bool CBeginSession::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvMeasure,
        &pvUnitsPerMeasure,
        &pvErrorReport,
        0L );
  }
//******************************************************************************
  bool CBeginSession::IsValid() const{
    return pvMeasure->IsValid() && pvUnitsPerMeasure->IsValid() &&
      pvErrorReport->IsValid();
  }
//******************************************************************************
  CAttributePtr& CBeginSession::Measure(){
    return this->pvMeasure;
  }
//******************************************************************************
  const CAttributePtr& CBeginSession::Measure() const{
    return this->pvMeasure;
  }
//******************************************************************************
  CAttributePtr& CBeginSession::UnitsPerMeasure(){
    return this->pvUnitsPerMeasure;
  }
//******************************************************************************
  const CAttributePtr& CBeginSession::UnitsPerMeasure() const {
    return this->pvUnitsPerMeasure;
  }
//******************************************************************************
  CAttributePtr& CBeginSession::ErrorReport(){
    return this->pvErrorReport;
  }
//******************************************************************************
  const CAttributePtr& CBeginSession::ErrorReport()  const{
    return this->pvErrorReport;
  }

}; /* namespace pcl6 */
