//*****************************************************************************
//        File: CSetCursor.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCURSOR_HPP__
#define __CSETCURSOR_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetCursor : public CPclOperator {
  public:
    CSetCursor();
    ~CSetCursor();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& Point();
    const CAttributePtr& Point() const;
  private:
    CAttributePtr pvPoint;
  };

}

#endif /* __CSETCURSOR_HPP__ */
