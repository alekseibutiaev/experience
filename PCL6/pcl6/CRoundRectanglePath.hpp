//*****************************************************************************
//        File: CRoundRectanglePath.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CROUNDRECTANGLEPATH_HPP__
#define __CROUNDRECTANGLEPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CRoundRectanglePath : public CPclOperator {
  public:
    CRoundRectanglePath();
    ~CRoundRectanglePath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& EllipseDimension();
    const CAttributePtr& EllipseDimension() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
  private:
    CAttributePtr pvEllipseDimension;
    CAttributePtr pvBoundingBox;
  };

}; /* namespace pcl6 */

#endif /* __CROUNDRECTANGLEPATH_HPP__ */
