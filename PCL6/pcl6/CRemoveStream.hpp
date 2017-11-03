//*****************************************************************************
//        File: CRemoveStream.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CREMOVESTREAM_HPP__
#define __CREMOVESTREAM_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CRemoveStream : public CPclOperator {
  public:
    CRemoveStream();
    ~CRemoveStream();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& StreamName();
    const CAttributePtr& StreamName() const;
  private:
    CAttributePtr pvStreamName;
  };

}

#endif /* __CREMOVESTREAM_HPP__ */
