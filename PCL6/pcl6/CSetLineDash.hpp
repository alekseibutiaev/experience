//*****************************************************************************
//        File: CSetLineDash.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETLINEDASH_HPP__
#define __CSETLINEDASH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CSetLineDash : public CPclOperator {
  public:
    CSetLineDash();
    ~CSetLineDash();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& DashOffset();
    const CAttributePtr& DashOffset() const;
    CAttributePtr& LineDashStyle();
    const CAttributePtr& LineDashStyle() const;
    CAttributePtr& SolidLine();
    const CAttributePtr& SolidLine() const;
  private:
    CAttributePtr pvDashOffset;
    CAttributePtr pvLineDashStyle;
    CAttributePtr pvSolidLine;
  };

}; /* namespace pcl6 */

#endif /* __CSETLINEDASH_HPP__ */
