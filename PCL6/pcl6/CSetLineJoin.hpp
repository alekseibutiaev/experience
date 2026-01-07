//*****************************************************************************
//        File: CSetLineJoin.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETLINEJOIN_HPP__
#define __CSETLINEJOIN_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetLineJoin : public CPclOperator {
  public:
    CSetLineJoin();
    ~CSetLineJoin();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& LineJoinStyle();
    const CAttributePtr& LineJoinStyle() const;
  private:
    CAttributePtr pvLineJoinStyle;
  };

}

#endif /* __CSETLINEJOIN_HPP__ */
