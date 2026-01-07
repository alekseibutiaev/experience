//*****************************************************************************
//        File: CSetMiterLimit.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETMITERLIMIT_HPP__
#define __CSETMITERLIMIT_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetMiterLimit : public CPclOperator {
  public:
    CSetMiterLimit();
    ~CSetMiterLimit();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& MiterLength ();
    const CAttributePtr& MiterLength () const;
  private:
    CAttributePtr pvMiterLength ;
  };

}

#endif /* __CSETMITERLIMIT_HPP__ */
