//*****************************************************************************
//        File: CBeginPage.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef CBEGINPAGE_HPP_
#define CBEGINPAGE_HPP_

#include "CPclOperator.hpp"

namespace pcl6 {

  class CBeginPage : public CPclOperator {
  public:
    CBeginPage();
    ~CBeginPage();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& Orientation();
    const CAttributePtr& Orientation() const;
    CAttributePtr& MediaSource();
    const CAttributePtr& MediaSource()  const;
    CAttributePtr& MediaSize();
    const CAttributePtr& MediaSize() const;
    CAttributePtr& CustomMediaSize();
    const CAttributePtr& CustomMediaSize() const;
    CAttributePtr& CustomMediaSizeUnits();
    const CAttributePtr& CustomMediaSizeUnits() const;
    CAttributePtr& MediaType();
    const CAttributePtr& MediaType() const;
    CAttributePtr& MediaDestination();
    const CAttributePtr& MediaDestination() const;
    CAttributePtr& SimplexPageMode();
    const CAttributePtr& SimplexPageMode() const;
    CAttributePtr& DuplexPageMode();
    const CAttributePtr& DuplexPageMode() const;
    CAttributePtr& DuplexPageSide();
    const CAttributePtr& DuplexPageSide() const;
  private:
    CAttributePtr pvOrientation;
    CAttributePtr pvMediaSource;
    CAttributePtr pvMediaSize;
    CAttributePtr pvCustomMediaSize;
    CAttributePtr pvCustomMediaSizeUnits;
    CAttributePtr pvMediaType;
    CAttributePtr pvMediaDestination;
    CAttributePtr pvSimplexPageMode;
    CAttributePtr pvDuplexPageMode;
    CAttributePtr pvDuplexPageSide;

  };

}

#endif /* CBEGINPAGE_HPP_ */
