//*****************************************************************************
//        File: CBeginImage.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEGINIMAGE_HPP__
#define __CBEGINIMAGE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CBeginImage : public CPclOperator {
  public:
    CBeginImage();
    ~CBeginImage();
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
  private:
    CAttributePtr pvColorDepth;
    CAttributePtr pvColorMapping;
    CAttributePtr pvDestinationSize;
    CAttributePtr pvSourceWidth;
    CAttributePtr pvSourceHeight;
  };


}; /* namespace pcl6 */

#endif /* __CBEGINIMAGE_HPP__ */
