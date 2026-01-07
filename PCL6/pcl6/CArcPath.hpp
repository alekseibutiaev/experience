//*****************************************************************************
//        File: CArcPath.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CARCPATH_HPP__
#define __CARCPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CArcPath : public CPclOperator {
  public:
    CArcPath();
    ~CArcPath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
    CAttributePtr& StartPoint();
    const CAttributePtr& StartPoint() const;
    CAttributePtr& EndPoint();
    const CAttributePtr& EndPoint() const;
    CAttributePtr& ArcDirection();
    const CAttributePtr& ArcDirection() const;
  private:
    CAttributePtr pvBoundingBox;
    CAttributePtr pvStartPoint;
    CAttributePtr pvEndPoint;
    CAttributePtr pvArcDirection;
  };


}; /* namespace pcl6 */

#endif /* __CARCPATH_HPP__ */
