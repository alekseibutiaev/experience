//*****************************************************************************
//        File: CSetPaintTxMode.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETPAINTTXMODE_HPP__
#define __CSETPAINTTXMODE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetPaintTxMode : public CPclOperator {
  public:
    CSetPaintTxMode();
    ~CSetPaintTxMode();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& TxMode();
    const CAttributePtr& TxMode() const;
  private:
    CAttributePtr pvTxMode;
  };

}

#endif /* __CSETPAINTTXMODE_HPP__ */
