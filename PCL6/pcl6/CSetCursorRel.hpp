//*****************************************************************************
//        File: CSetCursorRel.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCURSORREL_HPP__
#define __CSETCURSORREL_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCursorRel : public CPclOperator {
  public:
    CSetCursorRel();
    ~CSetCursorRel();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& Point();
    const CAttributePtr& Point() const;
  private:
    CAttributePtr pvPoint;
  };

}

#endif /* __CSETCURSORREL_HPP__ */
