//*****************************************************************************
//        File: CBeginFontHeader.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEGINFONTHEADER_HPP__
#define __CBEGINFONTHEADER_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CBeginFontHeader : public CPclOperator {
  public:
    CBeginFontHeader();
    ~CBeginFontHeader();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& FontName();
    const CAttributePtr& FontName() const;
    CAttributePtr& FontFormat();
    const CAttributePtr& FontFormat() const;
  private:
    CAttributePtr pvFontName;
    CAttributePtr pvFontFormat;
  };

}

#endif /* __CBEGINFONTHEADER_HPP__ */
