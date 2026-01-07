//*****************************************************************************
//        File: CReadRastPattern.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CREADRASTPATTERN_HPP__
#define __CREADRASTPATTERN_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
//  multiAttributeList ::= { CompressMode & StartLine & BlockHeight
//                              & {PadBytesMultiple}opt & {BlockByteLength}opt}

  class CReadRastPattern : public CPclOperator {
  public:
    CReadRastPattern();
    ~CReadRastPattern();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CompressMode();
    const CAttributePtr& CompressMode() const;
    CAttributePtr& StartLine();
    const CAttributePtr& StartLine() const;
    CAttributePtr& BlockHeight();
    const CAttributePtr& BlockHeight() const;
    CAttributePtr& PadBytesMultiple();
    const CAttributePtr& PadBytesMultiple() const;
    CAttributePtr& BlockByteLength();
    const CAttributePtr& BlockByteLength() const;
  private:
    CAttributePtr pvCompressMode;
    CAttributePtr pvStartLine;
    CAttributePtr pvBlockHeight;
    CAttributePtr pvPadBytesMultiple;
    CAttributePtr pvBlockByteLength;
  };


}; /* namespace pcl6 */

#endif /* __CREADRASTPATTERN_HPP__ */
