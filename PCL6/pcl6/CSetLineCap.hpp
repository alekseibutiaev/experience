//*****************************************************************************
//        File: CSetLineCap.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETLINECAP_HPP__
#define __CSETLINECAP_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetLineCap : public CPclOperator {
  public:
    CSetLineCap();
    ~CSetLineCap();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& LineCapStyle();
    const CAttributePtr& LineCapStyle() const;
  private:
    CAttributePtr pvLineCapStyle;
  };

}

#endif /* __CSETLINECAP_HPP__ */
