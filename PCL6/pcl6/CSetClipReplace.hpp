//*****************************************************************************
//        File: CSetClipReplace.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCLIPREPLACE_HPP__
#define __CSETCLIPREPLACE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetClipReplace : public CPclOperator {
  public:
    CSetClipReplace();
    ~CSetClipReplace();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ClipRegion();
    const CAttributePtr& ClipRegion() const;
  private:
    CAttributePtr pvClipRegion;
  };

}

#endif /* __CSETCLIPREPLACE_HPP__ */
