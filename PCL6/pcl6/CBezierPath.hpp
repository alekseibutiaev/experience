//*****************************************************************************
//        File: CBezierPath.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEZIERPATH_HPP__
#define __CBEZIERPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CBezierPath : public CPclOperator {
  public:
    CBezierPath();
    ~CBezierPath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& NumberOfPoints();
    const CAttributePtr& NumberOfPoints() const;
    CAttributePtr& PointType();
    const CAttributePtr& PointType() const;
    CAttributePtr& ControlPoint1();
    const CAttributePtr& ControlPoint1() const;
    CAttributePtr& ControlPoint2();
    const CAttributePtr& ControlPoint2() const;
    CAttributePtr& EndPoint();
    const CAttributePtr& EndPoint() const;
  private:
    CAttributePtr pvNumberOfPoints;
    CAttributePtr pvPointType;
    CAttributePtr pvControlPoint1;
    CAttributePtr pvControlPoint2;
    CAttributePtr pvEndPoint;
  };


}; /* namespace pcl6 */

#endif /* __CBEZIERPATH_HPP__ */
