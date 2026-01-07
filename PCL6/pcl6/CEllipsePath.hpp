//*****************************************************************************
//        File: CEllipsePath.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CELLIPSEPATH_HPP__
#define __CELLIPSEPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CEllipsePath : public CPclOperator {
  public:
    CEllipsePath();
    ~CEllipsePath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
  private:
    CAttributePtr pvBoundingBox;
  };

}

#endif /* __CELLIPSEPATH_HPP__ */
