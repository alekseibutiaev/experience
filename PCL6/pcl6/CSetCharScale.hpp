//*****************************************************************************
//        File: CSetCharScale.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCHARSCALE_HPP__
#define __CSETCHARSCALE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCharScale : public CPclOperator {
  public:
    CSetCharScale();
    ~CSetCharScale();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CharScale();
    const CAttributePtr& CharScale() const;
  private:
    CAttributePtr pvCharScale;
  };

}

#endif /* __CSETCHARSCALE_HPP__ */
