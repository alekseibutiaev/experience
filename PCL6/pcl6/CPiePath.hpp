//*****************************************************************************
//        File: CPiePath.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CPIEPATH_HPP__
#define __CPIEPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CPiePath : public CPclOperator {
  public:
    CPiePath();
    ~CPiePath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
    CAttributePtr& StartPoint();
    const CAttributePtr& StartPoint() const;
    CAttributePtr& EndPoint();
    const CAttributePtr& EndPoint() const;
  private:
    CAttributePtr pvBoundingBox;
    CAttributePtr pvStartPoint;
    CAttributePtr pvEndPoint;
  };

}; /* namespace pcl6 */

#endif /* __CPIEPATH_HPP__ */
