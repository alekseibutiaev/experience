//*****************************************************************************
//        File: CBeginStream.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CBEGINSTREAM_HPP__
#define __CBEGINSTREAM_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CBeginStream : public CPclOperator {
  public:
    CBeginStream();
    ~CBeginStream();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& StreamName();
    const CAttributePtr& StreamName() const;
  private:
    CAttributePtr pvStreamName;
  };

}

#endif /* __CBEGINSTREAM_HPP__ */
