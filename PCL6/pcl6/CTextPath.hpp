//*****************************************************************************
//        File: CTextPath.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CTEXTPATH_HPP__
#define __CTEXTPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CTextPath : public CPclOperator {
  public:
    CTextPath();
    ~CTextPath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& XSpacingData();
    const CAttributePtr& XSpacingData() const;
    CAttributePtr& YSpacingData();
    const CAttributePtr& YSpacingData() const;
    CAttributePtr& TextData();
    const CAttributePtr& TextData() const;
  private:
    CAttributePtr pvXSpacingData;
    CAttributePtr pvYSpacingData;
    CAttributePtr pvTextData;
  };

}; /* namespace pcl6 */

#endif /* __CTEXTPATH_HPP__ */
