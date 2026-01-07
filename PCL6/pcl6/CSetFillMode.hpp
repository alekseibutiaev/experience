//*****************************************************************************
//        File: CSetFillMode.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETFILLMODE_HPP__
#define __CSETFILLMODE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetFillMode : public CPclOperator {
  public:
    CSetFillMode();
    ~CSetFillMode();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& FillMode();
    const CAttributePtr& FillMode() const;
  private:
    CAttributePtr pvFillMode;
  };

}

#endif /* __CSETFILLMODE_HPP__ */
