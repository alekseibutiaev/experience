//*****************************************************************************
//        File: CSetClipIntersect.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCLIPINTERSECT_HPP__
#define __CSETCLIPINTERSECT_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetClipIntersect : public CPclOperator {
  public:
    CSetClipIntersect();
    ~CSetClipIntersect();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ClipRegion();
    const CAttributePtr& ClipRegion() const;
  private:
    CAttributePtr pvClipRegion;
  };

}

#endif /* __CSETCLIPINTERSECT_HPP__ */
