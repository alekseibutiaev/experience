//*****************************************************************************
//        File: CReadFontHeader.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CREADFONTHEADER_HPP__
#define __CREADFONTHEADER_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CReadFontHeader : public CPclOperator {
  public:
    CReadFontHeader();
    ~CReadFontHeader();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& FontHeaderLength();
    const CAttributePtr& FontHeaderLength() const;
  private:
    CAttributePtr pvFontHeaderLength;
  };

}

#endif /* __CREADFONTHEADER_HPP__ */
