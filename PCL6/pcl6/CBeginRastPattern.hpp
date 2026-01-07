//*****************************************************************************
//        File: CBeginRastPattern.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEGINRASTPATTERN_HPP__
#define __CBEGINRASTPATTERN_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CBeginRastPattern : public CPclOperator {
  public:
    CBeginRastPattern();
    ~CBeginRastPattern();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& ColorDepth();
    const CAttributePtr& ColorDepth() const;
    CAttributePtr& ColorMapping();
    const CAttributePtr& ColorMapping() const;
    CAttributePtr& DestinationSize();
    const CAttributePtr& DestinationSize() const;
    CAttributePtr& SourceWidth();
    const CAttributePtr& SourceWidth() const;
    CAttributePtr& SourceHeight();
    const CAttributePtr& SourceHeight() const;
    CAttributePtr& PatternDefineID();
    const CAttributePtr& PatternDefineID() const;
    CAttributePtr& PatternPersistence();
    const CAttributePtr& PatternPersistence() const;
    CAttributePtr& NewDestinationSize();
    const CAttributePtr& NewDestinationSize() const;
  private:
    CAttributePtr pvColorDepth;
    CAttributePtr pvColorMapping;
    CAttributePtr pvDestinationSize;
    CAttributePtr pvSourceWidth;
    CAttributePtr pvSourceHeight;
    CAttributePtr pvPatternDefineID;
    CAttributePtr pvPatternPersistence;
  };


}; /* namespace pcl6 */

#endif /* __CBEGINRASTPATTERN_HPP__ */
