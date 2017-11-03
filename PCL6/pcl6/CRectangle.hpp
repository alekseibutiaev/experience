//*****************************************************************************
//        File: CRectangle.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CRECTANGLE_HPP__
#define __CRECTANGLE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CRectangle : public CPclOperator {
  public:
    CRectangle();
    ~CRectangle();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
  private:
    CAttributePtr pvBoundingBox;
  };

}

#endif /* __CRECTANGLE_HPP__ */
