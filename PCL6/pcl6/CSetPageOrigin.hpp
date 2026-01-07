//*****************************************************************************
//        File: CSetPageOrigin.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef CSETPAGEORIGIN_HPP_
#define CSETPAGEORIGIN_HPP_

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetPageOrigin : public pcl6::CPclOperator {
  public:
    CSetPageOrigin();
    ~CSetPageOrigin();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& PageOrigin();
    const CAttributePtr& PageOrigin() const;
  private:
    CAttributePtr pvPageOrigin;
  };

}

#endif /* CSETPAGEORIGIN_HPP_ */
