//*****************************************************************************
//        File: CSetROP.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETROP_HPP__
#define __CSETROP_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetROP : public CPclOperator {
  public:
    CSetROP();
    ~CSetROP();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ROP();
    const CAttributePtr& ROP() const;
  private:
    CAttributePtr pvROP;
  };

}

#endif /* __CSETROP_HPP__ */
