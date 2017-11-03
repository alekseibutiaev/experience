//*****************************************************************************
//        File: CPclOperator.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include <new>
#include <cstdarg>
#include <iostream>

#include "Operator.hpp"
#include "ParserErrno.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

//******************************************************************************
  namespace {
    class CFindByAttributeId {
    public:
      CFindByAttributeId( const CAttributePtr& f_Attribute ) :
        pvAttribute( f_Attribute ){
      }
      bool operator()( const CAttributePtr& f_Attribut ) const{
        return pvAttribute->AttributeID() == f_Attribut->AttributeID();
      }
    private:
      const CAttributePtr& pvAttribute;
    };
  }; /* namespace */

//******************************************************************************
  CPclOperator::CPclOperator( const int& f_Tag ) : COperator( f_Tag ) {
  };
//******************************************************************************
  CPclOperator::~CPclOperator() {
  }
//******************************************************************************
  CPclOperatorPtr CPclOperator::Create( const Byte& f_Tag ){
    try {
      switch ( f_Tag ) {
        // PCL Operators
        case PclTag::eCloseDataSource :
          return CPclOperatorPtr( new CCloseDataSource() );
        case PclTag::eEndFontHeader :
          return CPclOperatorPtr( new CEndFontHeader() );
        case PclTag::eEndChar :
          return CPclOperatorPtr( new CEndChar() );
        case PclTag::eEndStream :
          return CPclOperatorPtr( new CEndStream() );
        case PclTag::ePopGS :
          return CPclOperatorPtr( new CPopGS() );
        case PclTag::ePushGS :
          return CPclOperatorPtr( new CPushGS() );
        case PclTag::eSetClipToPage :
          return CPclOperatorPtr( new CSetClipToPage() );
        case PclTag::eSetPageDefaultCTM :
          return CPclOperatorPtr( new CSetPageDefaultCTM() );
        case PclTag::eSetPathToClip :
          return CPclOperatorPtr( new CSetPathToClip() );
        case PclTag::eCloseSubPath :
          return CPclOperatorPtr( new CCloseSubPath() );
        case PclTag::eNewPath :
          return CPclOperatorPtr( new CNewPath() );
        case PclTag::ePaintPath :
          return CPclOperatorPtr( new CPaintPath() );
        case PclTag::eEndImage :
          return CPclOperatorPtr( new CEndImage() );
        case PclTag::eEndRastPattern :
          return CPclOperatorPtr( new CEndRastPattern() );
        case PclTag::eBeginScan :
          return CPclOperatorPtr( new CBeginScan() );
        case PclTag::eEndScan :
          return CPclOperatorPtr( new CEndScan() );
        case PclTag::eBeginSession :
          return CPclOperatorPtr( new CBeginSession() );
        case PclTag::eEndSession :
          return CPclOperatorPtr( new CEndSession() );
        case PclTag::eOpenDataSource :
          return CPclOperatorPtr( new COpenDataSource() );
        case PclTag::eBeginPage :
          return CPclOperatorPtr( new CBeginPage() );
        case PclTag::eSetPageOrigin :
          return CPclOperatorPtr( new CSetPageOrigin() );
        case PclTag::eSetPageScale :
          return CPclOperatorPtr( new CSetPageScale() );
        case PclTag::eSetClipMode :
          return CPclOperatorPtr( new CSetClipMode() );
        case PclTag::eSetROP :
          return CPclOperatorPtr( new CSetROP() );
        case PclTag::eSetCursor :
          return CPclOperatorPtr( new CSetCursor() );
        case PclTag::eLineRelPath :
          return CPclOperatorPtr( new CLineRelPath() );
        case PclTag::eSetColorSpace :
          return CPclOperatorPtr( new CSetColorSpace() );
        case PclTag::eSetPaintTxMode :
          return CPclOperatorPtr( new CSetPaintTxMode() );
        case PclTag::eSetSourceTxMode :
          return CPclOperatorPtr( new CSetSourceTxMode() );
        case PclTag::eSetBrushSource :
          return CPclOperatorPtr( new CSetBrushSource() );
        case PclTag::eSetPenSource :
          return CPclOperatorPtr( new CSetPenSource() );
        case PclTag::eSetFillMode :
          return CPclOperatorPtr( new CSetFillMode() );
        case PclTag::eRectanglePath :
          return CPclOperatorPtr( new CRectanglePath() );
        case PclTag::eBeginFontHeader :
          return CPclOperatorPtr( new CBeginFontHeader() );
        case PclTag::eReadFontHeader :
          return CPclOperatorPtr( new CReadFontHeader() );
        case PclTag::eBeginChar :
          return CPclOperatorPtr( new CBeginChar() );
        case PclTag::eReadChar :
          return CPclOperatorPtr( new CReadChar() );
        case PclTag::eSetFont :
          return CPclOperatorPtr( new CSetFont() );
        case PclTag::eSetCharScale :
          return CPclOperatorPtr( new CSetCharScale() );
        case PclTag::eText :
          return CPclOperatorPtr( new CText() );
        case PclTag::eSetClipRectangle :
          return CPclOperatorPtr( new CSetClipRectangle() );
        case PclTag::eBeginImage :
          return CPclOperatorPtr( new CBeginImage() );
        case PclTag::eReadImage :
          return CPclOperatorPtr( new CReadImage() );
        case PclTag::eSetClipReplace :
          return CPclOperatorPtr( new CSetClipReplace() );
        case PclTag::eEndPage :
          return CPclOperatorPtr( new CEndPage() );
        case PclTag::eSetCharAngle :
          return CPclOperatorPtr( new CSetCharAngle() );
        case PclTag::eSetLineJoin :
          return CPclOperatorPtr( new CSetLineJoin() );
        case PclTag::eSetLineCap :
          return CPclOperatorPtr( new CSetLineCap() );
        case PclTag::eSetPenWidth :
          return CPclOperatorPtr( new CSetPenWidth() );
        case PclTag::eSetLineDash :
          return CPclOperatorPtr( new CSetLineDash() );
        case PclTag::eRemoveFont :
          return CPclOperatorPtr( new CRemoveFont() );
        case PclTag::eBeginStream :
          return CPclOperatorPtr( new CBeginStream() );
        case PclTag::eComment :
          return CPclOperatorPtr( new CComment() );
        case PclTag::eEllipse :
          return CPclOperatorPtr( new CEllipse() );
        case PclTag::eEllipsePath :
          return CPclOperatorPtr( new CEllipsePath() );
        case PclTag::eExecStream :
          return CPclOperatorPtr( new CExecStream() );
        case PclTag::eReadStream :
          return CPclOperatorPtr( new CReadStream() );
        case PclTag::eRectangle :
          return CPclOperatorPtr( new CRectangle() );
        case PclTag::eRemoveStream :
          return CPclOperatorPtr( new CRemoveStream() );
        case PclTag::eScanLineRel :
          return CPclOperatorPtr( new CScanLineRel() );
        case PclTag::eSetCharAttributes :
          return CPclOperatorPtr( new CSetCharAttributes() );
        case PclTag::eSetCharBoldValue :
          return CPclOperatorPtr( new CSetCharBoldValue() );
        case PclTag::eSetCharShear :
          return CPclOperatorPtr( new CSetCharShear() );
        case PclTag::eSetCharSubMode :
          return CPclOperatorPtr( new CSetCharSubMode() );
        case PclTag::eSetClipIntersect :
          return CPclOperatorPtr( new CSetClipIntersect() );
        case PclTag::eSetCursorRel :
          return CPclOperatorPtr( new CSetCursorRel() );
        case PclTag::eSetMiterLimit :
          return CPclOperatorPtr( new CSetMiterLimit() );
        case PclTag::eSetPageRotation :
          return CPclOperatorPtr( new CSetPageRotation() );
        case PclTag::eTextPath :
          return CPclOperatorPtr( new CTextPath() );
        case PclTag::eChord :
          return CPclOperatorPtr( new CChord() );
        case PclTag::eChordPath :
          return CPclOperatorPtr( new CChordPath() );
        case PclTag::eLinePath :
          return CPclOperatorPtr( new CLinePath() );
        case PclTag::ePie :
          return CPclOperatorPtr( new CPie() );
        case PclTag::ePiePath :
          return CPclOperatorPtr( new CPiePath() );
        case PclTag::eRoundRectangle :
          return CPclOperatorPtr( new CRoundRectangle() );
        case PclTag::eRoundRectanglePath :
          return CPclOperatorPtr( new CRoundRectanglePath() );
        case PclTag::eArcPath :
          return CPclOperatorPtr( new CArcPath() );
        case PclTag::eBeginRastPattern :
          return CPclOperatorPtr( new CBeginRastPattern() );
        case PclTag::eReadRastPattern :
          return CPclOperatorPtr( new CReadRastPattern() );
        case PclTag::eBezierPath :
          return CPclOperatorPtr( new CBezierPath() );
        case PclTag::eBezierRelPath :
          return CPclOperatorPtr( new CBezierRelPath() );
        case PclTag::eSetHalftoneMethod :
          return CPclOperatorPtr( new CSetHalftoneMethod() );
        case PclTag::eVendorUnique :
          return CPclOperatorPtr( new CVendorUnique() );
        default :
          return CPclOperatorPtr();
        }
    }
    catch( std::bad_alloc ) {
      PCLErrno = PCLErr::AllocateObject;
      return CPclOperatorPtr();
    }
  }
//******************************************************************************
  bool CPclOperator::ptSetAttributes( const CAttributeArray& f_Atributes, ... ){
    va_list list;
    va_start( list, f_Atributes );
    CAttributePtr* attrPtr;
    CAttributeArray::const_iterator begin = f_Atributes.begin();
    CAttributeArray::const_iterator end = f_Atributes.end();
    while( ( attrPtr = va_arg( list, CAttributePtr* ) ) ) {
      CAttributeArray::const_iterator attr = std::find_if( begin, end,
          CFindByAttributeId( *attrPtr ) );
      if( attr != end ) {
        (*attrPtr)->Data() = (*attr)->Data();
      }
    }
    va_end( list );
    return IsValid();
  }

}; /* namespace pcl6 */
