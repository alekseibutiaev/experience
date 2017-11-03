//*****************************************************************************
//        File: CReadChar.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CREADCHAR_HPP__
#define __CREADCHAR_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CReadChar : public CPclOperator {
  public:
    CReadChar();
    ~CReadChar();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CharCode();
    const CAttributePtr& CharCode() const;
    CAttributePtr& CharDataSize();
    const CAttributePtr& CharDataSize() const;
  private:
    CAttributePtr pvCharCode;
    CAttributePtr pvCharDataSize;
  };

}

#endif /* __CREADCHAR_HPP__ */
