//*****************************************************************************
//        File: CSetCharBoldValue.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCHARBOLDVALUE_HPP__
#define __CSETCHARBOLDVALUE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCharBoldValue : public CPclOperator {
  public:
    CSetCharBoldValue();
    ~CSetCharBoldValue();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CharBoldValue();
    const CAttributePtr& CharBoldValue() const;
  private:
    CAttributePtr pvCharBoldValue;
  };

}

#endif /* __CSETCHARBOLDVALUE_HPP__ */
