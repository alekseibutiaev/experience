//*****************************************************************************
//        File: CEllipse.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CELLIPSE_HPP__
#define __CELLIPSE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CEllipse : public CPclOperator {
  public:
    CEllipse();
    ~CEllipse();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
  private:
    CAttributePtr pvBoundingBox;
  };

}

#endif /* __CELLIPSE_HPP__ */
