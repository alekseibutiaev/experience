//*****************************************************************************
//        File: CPclOperator.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CPCLOPERATOR_HPP__
#define __CPCLOPERATOR_HPP__

#include <iostream>
#include <boost/smart_ptr.hpp>

#include "COperator.hpp"

namespace pcl6 {

  namespace PclTag {
    enum TAG{
      // Reserved for future use.
      eBeginSession       = 0x41, //*
      eEndSession         = 0x42, // nullAttributeList
      eBeginPage          = 0x43, //*
      eEndPage            = 0x44,
      // Reserved for future use.
      eVendorUnique       = 0x46, // Not documentary operator
      eComment            = 0x47,
      eOpenDataSource     = 0x48, //*
      eCloseDataSource    = 0x49, // nullAttributeList
      // Reserved for future use.
      eBeginFontHeader    = 0x4f,
      eReadFontHeader     = 0x50,
      eEndFontHeader      = 0x51, // nullAttributeList
      eBeginChar          = 0x52,
      eReadChar           = 0x53,
      eEndChar            = 0x54, // nullAttributeList
      eRemoveFont         = 0x55,
      eSetCharAttributes  = 0x56,
      // Reserved for future use.
      eBeginStream        = 0x5b,
      eReadStream         = 0x5c,
      eEndStream          = 0x5d, // nullAttributeList
      eExecStream         = 0x5e,
      eRemoveStream       = 0x5f,
      ePopGS              = 0x60, // nullAttributeList
      ePushGS             = 0x61, // nullAttributeList
      eSetClipReplace     = 0x62,
      eSetBrushSource     = 0x63,
      eSetCharAngle       = 0x64,
      eSetCharScale       = 0x65,
      eSetCharShear       = 0x66,
      eSetClipIntersect   = 0x67,
      eSetClipRectangle   = 0x68,
      eSetClipToPage      = 0x69, // nullAttributeList
      eSetColorSpace      = 0x6a,
      eSetCursor          = 0x6b,
      eSetCursorRel       = 0x6c,
      eSetHalftoneMethod  = 0x6d,
      eSetFillMode        = 0x6e,
      eSetFont            = 0x6f,
      eSetLineDash        = 0x70,
      eSetLineCap         = 0x71,
      eSetLineJoin        = 0x72,
      eSetMiterLimit      = 0x73,
      eSetPageDefaultCTM  = 0x74, // nullAttributeList
      eSetPageOrigin      = 0x75, //*
      eSetPageRotation    = 0x76,
      eSetPageScale       = 0x77, //*
      eSetPaintTxMode     = 0x78,
      eSetPenSource       = 0x79,
      eSetPenWidth        = 0x7a,
      eSetROP             = 0x7b,
      eSetSourceTxMode    = 0x7c,
      eSetCharBoldValue   = 0x7d,
      // Reserved for future use.
      eSetClipMode        = 0x7f,
      eSetPathToClip      = 0x80, // nullAttributeList
      eSetCharSubMode     = 0x81,
      // Reserved for future use.
      eCloseSubPath       = 0x84, // nullAttributeList
      eNewPath            = 0x85, // nullAttributeList
      ePaintPath          = 0x86, // nullAttributeList
      // Reserved for future use.
      eArcPath            = 0x91,
      // Reserved for future use.
      eBezierPath         = 0x93,
      // Reserved for future use.
      eBezierRelPath      = 0x95,
      eChord              = 0x96,
      eChordPath          = 0x97,
      eEllipse            = 0x98,
      eEllipsePath        = 0x99,
      // Reserved for future use.
      eLinePath           = 0x9b,
      // Reserved for future use.
      eLineRelPath        = 0x9d,
      ePie                = 0x9e,
      ePiePath            = 0x9f,
      eRectangle          = 0xa0,
      eRectanglePath      = 0xa1,
      eRoundRectangle     = 0xa2,
      eRoundRectanglePath = 0xa3,
      // Reserved for future use.
      eText               = 0xa8,
      eTextPath           = 0xa9,
      // Reserved for future use.
      eBeginImage         = 0xb0,
      eReadImage          = 0xb1,
      eEndImage           = 0xb2, // nullAttributeList
      eBeginRastPattern   = 0xb3,
      eReadRastPattern    = 0xb4,
      eEndRastPattern     = 0xb5, // nullAttributeList
      eBeginScan          = 0xb6, // nullAttributeList
      // Reserved for future use.
      eEndScan            = 0xb8, // nullAttributeList
      eScanLineRel        = 0xb9,
      eDataLength         = 0xfa,
      eDataLengthByte     = 0xfb,
      eError              = 0x100
    };
  } /* PjlTag */
//*****************************************************************************
  class CPclOperator;
  typedef boost::shared_ptr<CPclOperator> CPclOperatorPtr;
//*****************************************************************************
  class CPclOperator : public COperator {
  public:
    virtual ~CPclOperator();
    static CPclOperatorPtr Create( const Byte& f_Tag );
    virtual bool SetAttributes( const CAttributeArray& f_Atributes ) = 0;
  protected:
    CPclOperator( const int& f_Tag );
    bool ptSetAttributes( const CAttributeArray& f_Atributes, ... );
  };
//*****************************************************************************

}; /* namespace pcl6 */


#endif /* __CPCLOPERATOR_HPP__ */
