/*
 * CreateAttribute.cpp
 *
 *  Created on: 28.11.2009
 *      Author: alexsy
 */

#include "CreateAttribute.hpp"
#include "CAttributeTag.hpp"

namespace pcl6 {

  // 2
  template <>
  CAttributePtr CreateAttribute< Attribute::ePaletteDepth >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePaletteDepth ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePaletteDepth >( AttributeIs::Status );
  // 3
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorSpace >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eColorSpace ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eColorSpace >( AttributeIs::Status );
  // 4
  template <>
  CAttributePtr CreateAttribute< Attribute::eNullBrush >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eNullBrush ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eNullBrush >( AttributeIs::Status );
  // 5
  template <>
  CAttributePtr CreateAttribute< Attribute::eNullPen >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eNullPen ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eNullPen >( AttributeIs::Status );
  // 6
  template <>
  CAttributePtr CreateAttribute< Attribute::ePaletteData >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePaletteData ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePaletteData >( AttributeIs::Status );
  // 8
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternSelectID >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePatternSelectID ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePatternSelectID >( AttributeIs::Status );
  // 9
  template <>
  CAttributePtr CreateAttribute< Attribute::eGrayLevel >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eGrayLevel ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eGrayLevel >( AttributeIs::Status );
  // 11
  template <>
  CAttributePtr CreateAttribute< Attribute::eRGBColor >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eRGBColor ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eRGBColor >( AttributeIs::Status );
  // 12
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternOrigin >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePatternOrigin ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePatternOrigin >( AttributeIs::Status );
  // 13
  template <>
  CAttributePtr CreateAttribute< Attribute::eNewDestinationSize >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eNewDestinationSize ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eNewDestinationSize >( AttributeIs::Status );
  // 14
  template <>
  CAttributePtr CreateAttribute< Attribute::ePrimaryArray >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePrimaryArray ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePrimaryArray >( AttributeIs::Status );
  // 15
  template <>
  CAttributePtr CreateAttribute< Attribute::ePrimaryDepth >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePrimaryDepth ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePrimaryDepth >( AttributeIs::Status );
  // 33
  template <>
  CAttributePtr CreateAttribute< Attribute::eDeviceMatrix >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDeviceMatrix ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDeviceMatrix >( AttributeIs::Status );
  // 34
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherMatrixDataType >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDitherMatrixDataType ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDitherMatrixDataType >( AttributeIs::Status );
  // 35
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherOrigin >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDitherOrigin ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDitherOrigin >( AttributeIs::Status );
  // 36
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaDestination >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eMediaDestination ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eMediaDestination >( AttributeIs::Status );
  // 37
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaSize >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eMediaSize ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eMediaSize >( AttributeIs::Status );
  // 38
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaSource >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eMediaSource ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eMediaSource >( AttributeIs::Status );
  // 39
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaType>( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eMediaType ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eMediaType >( AttributeIs::Status );
  // 40
  template <>
  CAttributePtr CreateAttribute< Attribute::eOrientation >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eOrientation ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eOrientation >( AttributeIs::Status );
  // 41
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageAngle >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePageAngle ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePageAngle >( AttributeIs::Status );
  // 42
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageOrigin >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePageOrigin ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePageOrigin >( AttributeIs::Status );
  // 43
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageScale >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePageScale ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePageScale >( AttributeIs::Status );
  // 44
  template <>
  CAttributePtr CreateAttribute< Attribute::eROP3 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eROP3 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eROP3 >( AttributeIs::Status );
  // 45
  template <>
  CAttributePtr CreateAttribute< Attribute::eTxMode >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eTxMode ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eTxMode >( AttributeIs::Status );
  // 47
  template <>
  CAttributePtr CreateAttribute< Attribute::eCustomMediaSize >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eCustomMediaSize ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCustomMediaSize >( AttributeIs::Status );
  // 48
  template <>
  CAttributePtr CreateAttribute< Attribute::eCustomMediaSizeUnits >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eCustomMediaSizeUnits ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCustomMediaSizeUnits >( AttributeIs::Status );
  // 49
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageCopies >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePageCopies ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePageCopies >( AttributeIs::Status );
  // 50
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherMatrixSize >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDitherMatrixSize ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDitherMatrixSize >( AttributeIs::Status );
  // 51
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherMatrixDepth >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDitherMatrixDepth ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDitherMatrixDepth >( AttributeIs::Status );
  // 52
  template <>
  CAttributePtr CreateAttribute< Attribute::eSimplexPageMode >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eSimplexPageMode ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eSimplexPageMode >( AttributeIs::Status );
  // 53
  template <>
  CAttributePtr CreateAttribute< Attribute::eDuplexPageMode >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDuplexPageMode ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDuplexPageMode >( AttributeIs::Status );
  // 54
  template <>
  CAttributePtr CreateAttribute< Attribute::eDuplexPageSide >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDuplexPageSide ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDuplexPageSide >( AttributeIs::Status );

  // 65
  template <>
  CAttributePtr CreateAttribute< Attribute::eArcDirection >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eArcDirection ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eArcDirection >( AttributeIs::Status );
  // 66
  template <>
  CAttributePtr CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eBoundingBox ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Status );
  // 67
  template <>
  CAttributePtr CreateAttribute< Attribute::eDashOffset >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDashOffset ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDashOffset >( AttributeIs::Status );
  // 68
  template <>
  CAttributePtr CreateAttribute< Attribute::eEllipseDimension >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eEllipseDimension ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eEllipseDimension >( AttributeIs::Status );
  // 69
  template <>
  CAttributePtr CreateAttribute< Attribute::eEndPoint >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eEndPoint ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eEndPoint >( AttributeIs::Status );
  // 70
  template <>
  CAttributePtr CreateAttribute< Attribute::eFillMode >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eFillMode ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eFillMode >( AttributeIs::Status );
  // 71
  template <>
  CAttributePtr CreateAttribute< Attribute::eLineCapStyle >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eLineCapStyle ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eLineCapStyle >( AttributeIs::Status );
  // 72
  template <>
  CAttributePtr CreateAttribute< Attribute::eLineJoinStyle >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eLineJoinStyle ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eLineJoinStyle >( AttributeIs::Status );
  // 73
  template <>
  CAttributePtr CreateAttribute< Attribute::eMiterLength >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eMiterLength ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eMiterLength >( AttributeIs::Status );
  // 74
  template <>
  CAttributePtr CreateAttribute< Attribute::eLineDashStyle >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eLineDashStyle ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eLineDashStyle >( AttributeIs::Status );
  // 75
  template <>
  CAttributePtr CreateAttribute< Attribute::ePenWidth >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePenWidth ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePenWidth >( AttributeIs::Status );
  // 76
  template <>
  CAttributePtr CreateAttribute< Attribute::ePoint >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePoint ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePoint >( AttributeIs::Status );
  // 77
  template <>
  CAttributePtr CreateAttribute< Attribute::eNumberOfPoints >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eNumberOfPoints ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eNumberOfPoints >( AttributeIs::Status );
  // 78
  template <>
  CAttributePtr CreateAttribute< Attribute::eSolidLine >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eSolidLine ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eSolidLine >( AttributeIs::Status );
  // 79
  template <>
  CAttributePtr CreateAttribute< Attribute::eStartPoint >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eStartPoint ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eStartPoint >( AttributeIs::Status );
  // 80
  template <>
  CAttributePtr CreateAttribute< Attribute::ePointType >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePointType ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePointType >( AttributeIs::Status );
  // 81
  template <>
  CAttributePtr CreateAttribute< Attribute::eControlPoint1 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eControlPoint1 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eControlPoint1 >( AttributeIs::Status );
  // 82
  template <>
  CAttributePtr CreateAttribute< Attribute::eControlPoint2 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eControlPoint2 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eControlPoint2 >( AttributeIs::Status );
  // 83
  template <>
  CAttributePtr CreateAttribute< Attribute::eClipRegion >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eClipRegion ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eClipRegion >( AttributeIs::Status );
  // 84
  template <>
  CAttributePtr CreateAttribute< Attribute::eClipMode >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eClipMode ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eClipMode >( AttributeIs::Status );

  // 98
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorDepth >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eColorDepth ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eColorDepth >( AttributeIs::Status );
  // 99
  template <>
  CAttributePtr CreateAttribute< Attribute::eBlockHeight >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eBlockHeight ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eBlockHeight >( AttributeIs::Status );
  // 100
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorMapping >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eColorMapping ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eColorMapping >( AttributeIs::Status );
  // 101
  template <>
  CAttributePtr CreateAttribute< Attribute::eCompressMode >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eCompressMode ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCompressMode >( AttributeIs::Status );
  // 102
  template <>
  CAttributePtr CreateAttribute< Attribute::eDestinationBox >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDestinationBox ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDestinationBox >( AttributeIs::Status );
  // 103
  template <>
  CAttributePtr CreateAttribute< Attribute::eDestinationSize >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eDestinationSize ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDestinationSize >( AttributeIs::Status );
  // 104
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternPersistence >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePatternPersistence ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePatternPersistence >( AttributeIs::Status );
  // 105
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternDefineID >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePatternDefineID ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePatternDefineID >( AttributeIs::Status );
  //
  // 107
  template <>
  CAttributePtr CreateAttribute< Attribute::eSourceHeight >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eSourceHeight ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eSourceHeight >( AttributeIs::Status );
  // 108
  template <>
  CAttributePtr CreateAttribute< Attribute::eSourceWidth >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eSourceWidth ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eSourceWidth >( AttributeIs::Status );
  // 109
  template <>
  CAttributePtr CreateAttribute< Attribute::eStartLine >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eStartLine ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eStartLine >( AttributeIs::Status );
  // 110
  template <>
  CAttributePtr CreateAttribute< Attribute::ePadBytesMultiple >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::ePadBytesMultiple ) );
  }
  template CAttributePtr CreateAttribute< Attribute::ePadBytesMultiple >( AttributeIs::Status );
  // 111
  template <>
  CAttributePtr CreateAttribute< Attribute::eBlockByteLength >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eBlockByteLength ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eBlockByteLength >( AttributeIs::Status );
  //
  // 115
  template <>
  CAttributePtr CreateAttribute< Attribute::eNumberOfScanLines >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eNumberOfScanLines ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eNumberOfScanLines >( AttributeIs::Status );
  //
  // 120
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorTreatment >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eColorTreatment ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eColorTreatment >( AttributeIs::Status );
  //
  // 129
  template <>
  CAttributePtr CreateAttribute< Attribute::eCommentData >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eCommentData ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCommentData >( AttributeIs::Status );
  // 130
  template <>
  CAttributePtr CreateAttribute< Attribute::eDataOrg >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eDataOrg ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eDataOrg >( AttributeIs::Status );
  //
  // 134
  template <>
  CAttributePtr CreateAttribute< Attribute::eMeasure >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eMeasure ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eMeasure >( AttributeIs::Status );
  //
  // 136
  template <>
  CAttributePtr CreateAttribute< Attribute::eSourceType >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eSourceType ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eSourceType >( AttributeIs::Status );
  // 137
  template <>
  CAttributePtr CreateAttribute< Attribute::eUnitsPerMeasure >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eUnitsPerMeasure ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eUnitsPerMeasure >( AttributeIs::Status );
  //
  // 139
  template <>
  CAttributePtr CreateAttribute< Attribute::eStreamName >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eStreamName ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eStreamName >( AttributeIs::Status );
  // 140
  template <>
  CAttributePtr CreateAttribute< Attribute::eStreamDataLength >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status, Attribute::eStreamDataLength ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eStreamDataLength >( AttributeIs::Status );
  //
  // 143
  template <>
  CAttributePtr CreateAttribute< Attribute::eErrorReport >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eErrorReport ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eErrorReport >( AttributeIs::Status );
  //
  // 145
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUExtension >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUExtension ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUExtension >( AttributeIs::Status );
  // 146
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUDataLength >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUDataLength ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUDataLength >( AttributeIs::Status );
  // 147
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr1 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr1 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr1 >( AttributeIs::Status );
  // 148
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr2 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr2 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr2 >( AttributeIs::Status );
  // 149
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr3 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr3 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr3 >( AttributeIs::Status );
  // 150
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr4 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr4 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr4 >( AttributeIs::Status );
  // 151
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr5 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr5 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr5 >( AttributeIs::Status );
  // 152
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr6 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr6 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr6 >( AttributeIs::Status );
  // 153
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr7 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr7 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr7 >( AttributeIs::Status );
  // 154
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr8 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr8 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr8 >( AttributeIs::Status );
  // 155
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr9 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr9 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr9 >( AttributeIs::Status );
  // 156
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr10 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr10 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr10 >( AttributeIs::Status );
  // 157
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr11 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr11 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr11 >( AttributeIs::Status );
  // 158
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr12 >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eVUAttr12 ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eVUAttr12 >( AttributeIs::Status );
  //
  // 161
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharAngle >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharAngle ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharAngle >( AttributeIs::Status );
  // 162
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharCode >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharCode ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharCode >( AttributeIs::Status );
  // 163
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharDataSize >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharDataSize ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharDataSize >( AttributeIs::Status );
  // 164
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharScale >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharScale ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharScale >( AttributeIs::Status );
  // 165
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharShear >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharShear ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharShear >( AttributeIs::Status );
  // 166
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharSize >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharSize ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharSize >( AttributeIs::Status );
  // 167
  template <>
  CAttributePtr CreateAttribute< Attribute::eFontHeaderLength >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eFontHeaderLength ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eFontHeaderLength >( AttributeIs::Status );
  // 168
  template <>
  CAttributePtr CreateAttribute< Attribute::eFontName >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eFontName ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eFontName >( AttributeIs::Status );
  // 169
  template <>
  CAttributePtr CreateAttribute< Attribute::eFontFormat >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eFontFormat ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eFontFormat >( AttributeIs::Status );
  // 170
  template <>
  CAttributePtr CreateAttribute< Attribute::eSymbolSet >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eSymbolSet ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eSymbolSet >( AttributeIs::Status );
  // 171
  template <>
  CAttributePtr CreateAttribute< Attribute::eTextData >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eTextData ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eTextData >( AttributeIs::Status );
  //
  // 172
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharSubModeArray >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharSubModeArray ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharSubModeArray >( AttributeIs::Status );
  //
  // 175
  template <>
  CAttributePtr CreateAttribute< Attribute::eXSpacingData >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eXSpacingData ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eXSpacingData >( AttributeIs::Status );
  // 177
  template <>
  CAttributePtr CreateAttribute< Attribute::eYSpacingData >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eYSpacingData ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eYSpacingData >( AttributeIs::Status );
  // 177
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharBoldValue >( AttributeIs::Status f_Status ) {
    return CAttributePtr(
      new CAttributeTag< AttributeTag::eAttr8 >( f_Status,  Attribute::eCharBoldValue ) );
  }
  template CAttributePtr CreateAttribute< Attribute::eCharBoldValue >( AttributeIs::Status );


}; /* namespace pcl6 */
