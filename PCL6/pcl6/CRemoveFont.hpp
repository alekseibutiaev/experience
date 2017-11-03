//*****************************************************************************
//        File: CRemoveFont.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CREMOVEFONT_HPP__
#define __CREMOVEFONT_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CRemoveFont : public CPclOperator {
  public:
    CRemoveFont();
    ~CRemoveFont();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& FontName();
    const CAttributePtr& FontName() const;
  private:
    CAttributePtr pvFontName;
  };

}

#endif /* __CREMOVEFONT_HPP__ */
