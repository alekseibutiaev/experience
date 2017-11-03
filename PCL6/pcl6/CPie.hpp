//*****************************************************************************
//        File: CPie.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CPIE_HPP__
#define __CPIE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CPie : public CPclOperator {
  public:
    CPie();
    ~CPie();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& BoundingBox();
    const CAttributePtr& BoundingBox() const;
    CAttributePtr& StartPoint();
    const CAttributePtr& StartPoint() const;
    CAttributePtr& ErrorReport();
    const CAttributePtr& ErrorReport() const;
  private:
    CAttributePtr pvBoundingBox;
    CAttributePtr pvStartPoint;
    CAttributePtr pvErrorReport;
  };

}; /* namespace pcl6 */

#endif /* __CPIE_HPP__ */
