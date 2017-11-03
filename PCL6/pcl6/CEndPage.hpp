//*****************************************************************************
//        File: CEndPage.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CENDPAGE_HPP__
#define __CENDPAGE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CEndPage : public CPclOperator {
  public:
    CEndPage();
    ~CEndPage();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& PageCopies();
    const CAttributePtr& PageCopies() const;
  private:
    CAttributePtr pvPageCopies;
  };

}

#endif /* __CENDPAGE_HPP__ */
