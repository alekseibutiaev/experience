//*****************************************************************************
//        File: CSetCharAttributes.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCHARATTRIBUTES_HPP__
#define __CSETCHARATTRIBUTES_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCharAttributes : public CPclOperator {
  public:
    CSetCharAttributes();
    ~CSetCharAttributes();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ClipMode();
    const CAttributePtr& ClipMode() const;
  private:
    CAttributePtr pvClipMode;
  };

}

#endif /* __CSETCHARATTRIBUTES_HPP__ */
