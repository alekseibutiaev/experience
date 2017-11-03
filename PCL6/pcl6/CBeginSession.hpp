//*****************************************************************************
//        File: CBeginSession.hpp
//     Project: kopirkin
//  Created on: 28.11.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEGINSESSION_HPP__
#define __CBEGINSESSION_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CBeginSession : public CPclOperator {
  public:
    CBeginSession();
    ~CBeginSession();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& Measure();
    const CAttributePtr& Measure() const;
    CAttributePtr& UnitsPerMeasure();
    const CAttributePtr& UnitsPerMeasure() const;
    CAttributePtr& ErrorReport();
    const CAttributePtr& ErrorReport() const;
  private:
    CAttributePtr pvMeasure;
    CAttributePtr pvUnitsPerMeasure;
    CAttributePtr pvErrorReport;
  };

}; /* namespace pcl6 */

#endif /* __CBEGINSESSION_HPP__ */
