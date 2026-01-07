//*****************************************************************************
//        File: CSetSourceTxMode.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETSOURCETXMODE_HPP__
#define __CSETSOURCETXMODE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetSourceTxMode : public CPclOperator {
  public:
    CSetSourceTxMode();
    ~CSetSourceTxMode();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& TxMode();
    const CAttributePtr& TxMode() const;
  private:
    CAttributePtr pvTxMode;
  };

}

#endif /* __CSETSOURCETXMODE_HPP__ */
