//*****************************************************************************
//        File: CScanLineRel.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSCANLINEREL_HPP__
#define __CSCANLINEREL_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CScanLineRel : public CPclOperator {
  public:
    CScanLineRel();
    ~CScanLineRel();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& NumberOfScanLines();
    const CAttributePtr& NumberOfScanLines() const;
  private:
    CAttributePtr pvNumberOfScanLines;
  };

}

#endif /* __CSCANLINEREL_HPP__ */
