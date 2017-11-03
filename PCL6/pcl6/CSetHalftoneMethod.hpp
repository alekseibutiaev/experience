//*****************************************************************************
//        File: CSetHalftoneMethod.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETHALFTONEMETHOD_HPP__
#define __CSETHALFTONEMETHOD_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CSetHalftoneMethod : public CPclOperator {
  public:
    CSetHalftoneMethod();
    ~CSetHalftoneMethod();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& DitherOrigin();
    const CAttributePtr& DitherOrigin() const;
    CAttributePtr& DeviceMatrix();
    const CAttributePtr& DeviceMatrix() const;
    CAttributePtr& DitherMatrixDataType();
    const CAttributePtr& DitherMatrixDataType() const;
    CAttributePtr& DitherMatrixSize();
    const CAttributePtr& DitherMatrixSize() const;
    CAttributePtr& DitherMatrixDepth();
    const CAttributePtr& DitherMatrixDepth() const;
  private:
    CAttributePtr pvDitherOrigin;
    CAttributePtr pvDeviceMatrix;
    CAttributePtr pvDitherMatrixDataType;
    CAttributePtr pvDitherMatrixSize;
    CAttributePtr pvDitherMatrixDepth;
  };


}; /* namespace pcl6 */

#endif /* __CSETHALFTONEMETHOD_HPP__ */
