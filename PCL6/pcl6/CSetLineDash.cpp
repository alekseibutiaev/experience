//*****************************************************************************
//        File: CSetLineDash.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetLineDash.hpp"

namespace pcl6 {

//******************************************************************************
  CSetLineDash::CSetLineDash() : CPclOperator( PclTag::eSetLineDash ),
    pvDashOffset( CreateAttribute< Attribute::eDashOffset >( AttributeIs::Optional ) ),
    pvLineDashStyle( CreateAttribute< Attribute::eLineDashStyle >( AttributeIs::Obligatory ) ),
    pvSolidLine( CreateAttribute< Attribute::eSolidLine >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetLineDash::~CSetLineDash() {
  }
//******************************************************************************
  bool CSetLineDash::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvDashOffset,
        &pvLineDashStyle,
        &pvSolidLine,
        0L );
  }
//******************************************************************************
  bool CSetLineDash::IsValid() const{
    return ( pvDashOffset->IsValid() && pvLineDashStyle->IsValid() ) ||
      pvSolidLine->IsValid();
  }
//******************************************************************************
  CAttributePtr& CSetLineDash::DashOffset(){
    return this->pvDashOffset;
  }
//******************************************************************************
  const CAttributePtr& CSetLineDash::DashOffset() const{
    return this->pvDashOffset;
  }
//******************************************************************************
  CAttributePtr& CSetLineDash::LineDashStyle(){
    return this->pvLineDashStyle;
  }
//******************************************************************************
  const CAttributePtr& CSetLineDash::LineDashStyle() const {
    return this->pvLineDashStyle;
  }
//******************************************************************************
  CAttributePtr& CSetLineDash::SolidLine(){
    return this->pvSolidLine;
  }
//******************************************************************************
  const CAttributePtr& CSetLineDash::SolidLine()  const{
    return this->pvSolidLine;
  }

}; /* namespace pcl6 */
