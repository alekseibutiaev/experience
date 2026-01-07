//*****************************************************************************
//        File: CSetCharShear.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCHARSHEAR_HPP__
#define __CSETCHARSHEAR_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCharShear : public CPclOperator {
  public:
    CSetCharShear();
    ~CSetCharShear();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CharShear();
    const CAttributePtr& CharShear() const;
  private:
    CAttributePtr pvCharShear;
  };

}

#endif /* __CSETCHARSHEAR_HPP__ */
