//*****************************************************************************
//        File: CSetPenSource.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CSETPENSOURCE_HPP__
#define __CSETPENSOURCE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CSetPenSource : public CPclOperator {
  public:
    CSetPenSource();
    ~CSetPenSource();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& RGBColor();
    const CAttributePtr& RGBColor() const;
    CAttributePtr& GrayLevel();
    const CAttributePtr& GrayLevel() const;
    CAttributePtr& NullPen();
    const CAttributePtr& NullPen() const;
    CAttributePtr& PrimaryArray();
    const CAttributePtr& PrimaryArray() const;
    CAttributePtr& PrimaryDepth();
    const CAttributePtr& PrimaryDepth() const;
    CAttributePtr& PatternSelectID();
    const CAttributePtr& PatternSelectID() const;
    CAttributePtr& PatternOrigin();
    const CAttributePtr& PatternOrigin() const;
    CAttributePtr& NewDestinationSize();
    const CAttributePtr& NewDestinationSize() const;
  private:
    CAttributePtr pvRGBColor;
    CAttributePtr pvGrayLevel;
    CAttributePtr pvNullPen;
    CAttributePtr pvPrimaryArray;
    CAttributePtr pvPrimaryDepth;
    CAttributePtr pvPatternSelectID;
    CAttributePtr pvPatternOrigin;
    CAttributePtr pvNewDestinationSize;
  };


}; /* namespace pcl6 */

#endif /* __CSETPENSOURCE_HPP__ */
