//*****************************************************************************
//        File: CScanLineRel.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CScanLineRel.hpp"

namespace pcl6 {
//******************************************************************************
  CScanLineRel::CScanLineRel() : CPclOperator( PclTag::eScanLineRel ),
    pvNumberOfScanLines( CreateAttribute< Attribute::eNumberOfScanLines >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CScanLineRel::~CScanLineRel() {
  }
//******************************************************************************
  bool CScanLineRel::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvNumberOfScanLines,
        0L );
  }
//******************************************************************************
  bool CScanLineRel::IsValid() const{
    return pvNumberOfScanLines->IsValid();
  }
//******************************************************************************
  CAttributePtr& CScanLineRel::NumberOfScanLines(){
    return this->pvNumberOfScanLines;
  }
//******************************************************************************
  const CAttributePtr& CScanLineRel::NumberOfScanLines() const{
    return this->pvNumberOfScanLines;
  }

}
