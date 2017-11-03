//*****************************************************************************
//        File: CRectanglePath.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CRECTANGLEPATH_HPP__
#define __CRECTANGLEPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CRectanglePath : public CPclOperator {
  public:
    CRectanglePath();
    ~CRectanglePath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
  private:
    CAttributePtr pvBoundingBox;
  };

}

#endif /* __CRECTANGLEPATH_HPP__ */
