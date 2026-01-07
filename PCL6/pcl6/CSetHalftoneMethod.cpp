//*****************************************************************************
//        File: CSetHalftoneMethod.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CSetHalftoneMethod.hpp"

namespace pcl6 {

//******************************************************************************
  CSetHalftoneMethod::CSetHalftoneMethod() : CPclOperator( PclTag::eSetHalftoneMethod ),
    pvDitherOrigin( CreateAttribute< Attribute::eDitherOrigin >( AttributeIs::Optional ) ),
    pvDeviceMatrix( CreateAttribute< Attribute::eDeviceMatrix >( AttributeIs::Obligatory ) ),
    pvDitherMatrixDataType( CreateAttribute< Attribute::eDitherMatrixDataType >( AttributeIs::Obligatory ) ),
    pvDitherMatrixSize( CreateAttribute< Attribute::eDitherMatrixSize >( AttributeIs::Obligatory ) ),
    pvDitherMatrixDepth( CreateAttribute< Attribute::eDitherMatrixDepth >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CSetHalftoneMethod::~CSetHalftoneMethod() {
  }
//******************************************************************************
  bool CSetHalftoneMethod::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvDitherOrigin,
        &pvDeviceMatrix,
        &pvDitherMatrixDataType,
        &pvDitherMatrixSize,
        &pvDitherMatrixDepth,
        0L );
  }
//******************************************************************************
  bool CSetHalftoneMethod::IsValid() const{
    return pvDitherOrigin->IsValid() && ( pvDeviceMatrix->IsValid() &&
      ( pvDitherMatrixSize->IsValid() && pvDitherMatrixDepth->IsValid() &&
        pvDitherMatrixDataType->IsValid() ) );
  }
//******************************************************************************
  CAttributePtr& CSetHalftoneMethod::DitherOrigin(){
    return this->pvDitherOrigin;
  }
//******************************************************************************
  const CAttributePtr& CSetHalftoneMethod::DitherOrigin() const{
    return this->pvDitherOrigin;
  }
//******************************************************************************
  CAttributePtr& CSetHalftoneMethod::DeviceMatrix(){
    return this->pvDeviceMatrix;
  }
//******************************************************************************
  const CAttributePtr& CSetHalftoneMethod::DeviceMatrix() const {
    return this->pvDeviceMatrix;
  }
//******************************************************************************
  CAttributePtr& CSetHalftoneMethod::DitherMatrixDataType(){
    return this->pvDitherMatrixDataType;
  }
//******************************************************************************
  const CAttributePtr& CSetHalftoneMethod::DitherMatrixDataType()  const{
    return this->pvDitherMatrixDataType;
  }
//******************************************************************************
  CAttributePtr& CSetHalftoneMethod::DitherMatrixSize(){
    return this->pvDitherMatrixSize;
  }
//******************************************************************************
  const CAttributePtr& CSetHalftoneMethod::DitherMatrixSize() const{
    return this->pvDitherMatrixSize;
  }
//******************************************************************************
  CAttributePtr& CSetHalftoneMethod::DitherMatrixDepth(){
    return this->pvDitherMatrixDepth;
  }
//******************************************************************************
  const CAttributePtr& CSetHalftoneMethod::DitherMatrixDepth() const{
    return this->pvDitherMatrixDepth;
  }

}; /* namespace pcl6 */
