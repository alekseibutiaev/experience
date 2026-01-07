//*****************************************************************************
//        File: CSetPenWidth.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETPENWIDTH_HPP__
#define __CSETPENWIDTH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetPenWidth : public CPclOperator {
  public:
    CSetPenWidth();
    ~CSetPenWidth();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& PenWidth();
    const CAttributePtr& PenWidth() const;
  private:
    CAttributePtr pvPenWidth;
  };

}

#endif /* __CSETPENWIDTH_HPP__ */
