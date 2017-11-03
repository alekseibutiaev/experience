//*****************************************************************************
//        File: CRoundRectangle.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CROUNDRECTANGLE_HPP__
#define __CROUNDRECTANGLE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CRoundRectangle : public CPclOperator {
  public:
    CRoundRectangle();
    ~CRoundRectangle();
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

#endif /* __CROUNDRECTANGLE_HPP__ */
