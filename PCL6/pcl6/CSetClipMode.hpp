//*****************************************************************************
//        File: CSetClipMode.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCLIPMODE_HPP__
#define __CSETCLIPMODE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetClipMode : public CPclOperator {
  public:
    CSetClipMode();
    ~CSetClipMode();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ClipMode();
    const CAttributePtr& ClipMode() const;
  private:
    CAttributePtr pvClipMode;
  };

}

#endif /* __CSETCLIPMODE_HPP__ */
