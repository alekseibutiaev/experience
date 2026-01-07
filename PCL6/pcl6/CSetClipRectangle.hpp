//*****************************************************************************
//        File: CSetClipRectangle.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCLIPRECTANGLE_HPP__
#define __CSETCLIPRECTANGLE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetClipRectangle : public CPclOperator {
  public:
    CSetClipRectangle();
    ~CSetClipRectangle();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ClipRegion();
    const CAttributePtr& ClipRegion() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
  private:
    CAttributePtr pvClipRegion;
    CAttributePtr pvBoundingBox;
  };

}

#endif /* __CSETCLIPRECTANGLE_HPP__ */
