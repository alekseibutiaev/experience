//*****************************************************************************
//        File: CSetCharAngle.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCHARANGLE_HPP__
#define __CSETCHARANGLE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCharAngle : public CPclOperator {
  public:
    CSetCharAngle();
    ~CSetCharAngle();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CharAngle();
    const CAttributePtr& CharAngle() const;
  private:
    CAttributePtr pvCharAngle;
  };

}

#endif /* __CSETCHARANGLE_HPP__ */
