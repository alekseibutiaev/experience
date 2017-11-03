//*****************************************************************************
//        File: CSetCharSubMode.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCHARSUBMODE_HPP__
#define __CSETCHARSUBMODE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCharSubMode : public CPclOperator {
  public:
    CSetCharSubMode();
    ~CSetCharSubMode();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CharSubModeArray();
    const CAttributePtr& CharSubModeArray() const;
  private:
    CAttributePtr pvCharSubModeArray;
  };

}

#endif /* __CSETCHARSUBMODE_HPP__ */
