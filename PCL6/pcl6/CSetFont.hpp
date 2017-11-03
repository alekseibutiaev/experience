//*****************************************************************************
//        File: CSetFont.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETFONT_HPP__
#define __CSETFONT_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CSetFont : public CPclOperator {
  public:
    CSetFont();
    ~CSetFont();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& SymbolSet();
    const CAttributePtr& SymbolSet() const;
    CAttributePtr& CharSize();
    const CAttributePtr& CharSize() const;
    CAttributePtr& FontName();
    const CAttributePtr& FontName() const;
  private:
    CAttributePtr pvSymbolSet;
    CAttributePtr pvCharSize;
    CAttributePtr pvFontName;
  };

}; /* namespace pcl6 */

#endif /* __CSETFONT_HPP__ */
