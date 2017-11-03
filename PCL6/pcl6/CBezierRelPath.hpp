//*****************************************************************************
//        File: CBezierRelPath.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEZIERRELPATH_HPP__
#define __CBEZIERRELPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CBezierRelPath : public CPclOperator {
  public:
    CBezierRelPath();
    ~CBezierRelPath();
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

#endif /* __CBEZIERRELPATH_HPP__ */
