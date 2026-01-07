//*****************************************************************************
//        File: CLinePath.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CLINEPATH_HPP__
#define __CLINEPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CLinePath : public CPclOperator {
  public:
    CLinePath();
    ~CLinePath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& EndPoint();
    const CAttributePtr& EndPoint() const;
    CAttributePtr& NumberOfPoints();
    const CAttributePtr& NumberOfPoints() const;
    CAttributePtr& PointType();
    const CAttributePtr& PointType() const;
  private:
    CAttributePtr pvEndPoint;
    CAttributePtr pvNumberOfPoints;
    CAttributePtr pvPointType;
  };

}; /* namespace pcl6 */

#endif /* __CLINEPATH_HPP__ */
