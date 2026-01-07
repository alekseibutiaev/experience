//*****************************************************************************
//        File: CSetPageRotation.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETPAGEROTATION_HPP__
#define __CSETPAGEROTATION_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetPageRotation : public CPclOperator {
  public:
    CSetPageRotation();
    ~CSetPageRotation();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& PageAngle ();
    const CAttributePtr& PageAngle () const;
  private:
    CAttributePtr pvPageAngle ;
  };

}

#endif /* __CSETPAGEROTATION_HPP__ */
