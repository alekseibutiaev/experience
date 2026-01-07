//*****************************************************************************
//        File: CText.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CTEXT_HPP__
#define __CTEXT_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CText : public CPclOperator {
  public:
    CText();
    ~CText();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& TextData();
    const CAttributePtr& TextData() const;
    CAttributePtr& YSpacingData();
    const CAttributePtr& YSpacingData() const;
    CAttributePtr& XSpacingData();
    const CAttributePtr& XSpacingData() const;
  private:
    CAttributePtr pvTextData;
    CAttributePtr pvYSpacingData;
    CAttributePtr pvXSpacingData;
  };

}; /* namespace pcl6 */

#endif /* __CTEXT_HPP__ */
