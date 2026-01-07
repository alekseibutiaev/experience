//*****************************************************************************
//        File: CSetColorSpace.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETCOLORSPACE_HPP__
#define __CSETCOLORSPACE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CSetColorSpace : public CPclOperator {
  public:
    CSetColorSpace();
    ~CSetColorSpace();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ColorSpace();
    const CAttributePtr& ColorSpace() const;
    CAttributePtr& PaletteData();
    const CAttributePtr& PaletteData() const;
    CAttributePtr& PaletteDepth();
    const CAttributePtr& PaletteDepth() const;
  private:
    CAttributePtr pvColorSpace;
    CAttributePtr pvPaletteData;
    CAttributePtr pvPaletteDepth;
  };

}; /* namespace pcl6 */

#endif /* __CSETCOLORSPACE_HPP__ */
