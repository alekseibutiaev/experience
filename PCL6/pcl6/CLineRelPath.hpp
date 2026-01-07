//*****************************************************************************
//        File: CLineRelPath.hpp
//     Project: kopirkin
//  Created on: 28.11.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CLINERELPATH_HPP__
#define __CLINERELPATH_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CLineRelPath : public CPclOperator {
  public:
    CLineRelPath();
    ~CLineRelPath();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& EndPoint();
    const CAttributePtr& EndPoint() const;
    CAttributePtr& NumberOfPoints();
    const CAttributePtr& NumberOfPoints() const;
    CAttributePtr& PointType();
    const CAttributePtr& PointType() const;
  private:
    CAttributePtr pvEndPoint;
    CAttributePtr pvNumberOfPoints;
    CAttributePtr pvPointType;
  };

}; /* namespace pcl6 */

#endif /* __CLINERELPATH_HPP__ */
