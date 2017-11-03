//*****************************************************************************
//        File: CReadStream.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CREADSTREAM_HPP__
#define __CREADSTREAM_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CReadStream : public CPclOperator {
  public:
    CReadStream();
    ~CReadStream();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& StreamDataLength();
    const CAttributePtr& StreamDataLength() const;
  private:
    CAttributePtr pvStreamDataLength;
  };

}

#endif /* __CREADSTREAM_HPP__ */
