//*****************************************************************************
//        File: CExecStream.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CEXECSTREAM_HPP__
#define __CEXECSTREAM_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CExecStream : public CPclOperator {
  public:
    CExecStream();
    ~CExecStream();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& StreamName();
    const CAttributePtr& StreamName() const;
  private:
    CAttributePtr pvStreamName;
  };

}

#endif /* __CEXECSTREAM_HPP__ */
