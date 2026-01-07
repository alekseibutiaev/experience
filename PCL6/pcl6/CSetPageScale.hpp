//*****************************************************************************
//        File: CSetPageScale.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef CSETPAGESCALE_HPP_
#define CSETPAGESCALE_HPP_

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CSetPageScale : public CPclOperator {
  public:
    CSetPageScale();
    ~CSetPageScale();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& PageScale();
    const CAttributePtr& PageScale() const;
    CAttributePtr& Measure();
    const CAttributePtr& Measure() const;
    CAttributePtr& UnitsPerMeasure();
    const CAttributePtr& UnitsPerMeasure() const;
  private:
    CAttributePtr pvPageScale;
    CAttributePtr pvMeasure;
    CAttributePtr pvUnitsPerMeasure;

  };

}

#endif /* CSETPAGESCALE_HPP_ */
