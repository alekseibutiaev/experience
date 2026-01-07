//*****************************************************************************
//        File: CBeginChar.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEGINCHAR_HPP__
#define __CBEGINCHAR_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CBeginChar : public CPclOperator {
  public:
    CBeginChar();
    ~CBeginChar();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& FontName();
    const CAttributePtr& FontName() const;
  private:
    CAttributePtr pvFontName;
  };

}

#endif /* __CBEGINCHAR_HPP__ */
