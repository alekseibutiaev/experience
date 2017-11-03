/*
 * CreateAttribute.hpp
 *
 *  Created on: 28.11.2009
 *      Author: alexsy
 */

#ifndef __CREATEATTRIBUTE_HPP__
#define __CREATEATTRIBUTE_HPP__

#include "AttributeID.hpp"
#include "CAttribute.hpp"

namespace pcl6 {

  template < int ATTRID >
  CAttributePtr CreateAttribute( AttributeIs::Status f_Status ) {
    class Unknown_Attribute_ID;
    Unknown_Attribute_ID();
    return CAttributePtr();
  }

  // 2
  template <>
  CAttributePtr CreateAttribute< Attribute::ePaletteDepth >( AttributeIs::Status f_Status );
  // 3
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorSpace >( AttributeIs::Status f_Status );
  // 4
  template <>
  CAttributePtr CreateAttribute< Attribute::eNullBrush >( AttributeIs::Status f_Status );
  // 5
  template <>
  CAttributePtr CreateAttribute< Attribute::eNullPen >( AttributeIs::Status f_Status );
  // 6
  template <>
  CAttributePtr CreateAttribute< Attribute::ePaletteData >( AttributeIs::Status f_Status );
  // 8
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternSelectID >( AttributeIs::Status f_Status );
  // 9
  template <>
  CAttributePtr CreateAttribute< Attribute::eGrayLevel >( AttributeIs::Status f_Status );
  // 11
  template <>
  CAttributePtr CreateAttribute< Attribute::eRGBColor >( AttributeIs::Status f_Status );
  // 12
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternOrigin >( AttributeIs::Status f_Status );
  // 13
  template <>
  CAttributePtr CreateAttribute< Attribute::eNewDestinationSize >( AttributeIs::Status f_Status );
  // 14
  template <>
  CAttributePtr CreateAttribute< Attribute::ePrimaryArray >( AttributeIs::Status f_Status );
  // 15
  template <>
  CAttributePtr CreateAttribute< Attribute::ePrimaryDepth >( AttributeIs::Status f_Status );
  // 33
  template <>
  CAttributePtr CreateAttribute< Attribute::eDeviceMatrix >( AttributeIs::Status f_Status );
  // 34
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherMatrixDataType >( AttributeIs::Status f_Status );
  // 35
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherOrigin >( AttributeIs::Status f_Status );
  // 36
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaDestination >( AttributeIs::Status f_Status );
  // 37
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaSize >( AttributeIs::Status f_Status );
  // 38
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaSource >( AttributeIs::Status f_Status );
  // 39
  template <>
  CAttributePtr CreateAttribute< Attribute::eMediaType >( AttributeIs::Status f_Status );
  // 40
  template <>
  CAttributePtr CreateAttribute< Attribute::eOrientation >( AttributeIs::Status f_Status );
  // 41
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageAngle >( AttributeIs::Status f_Status );
  // 42
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageOrigin >( AttributeIs::Status f_Status );
  // 43
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageScale >( AttributeIs::Status f_Status );
  // 44
  template <>
  CAttributePtr CreateAttribute< Attribute::eROP3 >( AttributeIs::Status f_Status );
  // 45
  template <>
  CAttributePtr CreateAttribute< Attribute::eTxMode >( AttributeIs::Status f_Status );
  // 47
  template <>
  CAttributePtr CreateAttribute< Attribute::eCustomMediaSize >( AttributeIs::Status f_Status );
  // 48
  template <>
  CAttributePtr CreateAttribute< Attribute::eCustomMediaSizeUnits >( AttributeIs::Status f_Status );
  // 49
  template <>
  CAttributePtr CreateAttribute< Attribute::ePageCopies >( AttributeIs::Status f_Status );
  // 50
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherMatrixSize >( AttributeIs::Status f_Status );
  // 51
  template <>
  CAttributePtr CreateAttribute< Attribute::eDitherMatrixDepth >( AttributeIs::Status f_Status );
  // 52
  template <>
  CAttributePtr CreateAttribute< Attribute::eSimplexPageMode >( AttributeIs::Status f_Status );
  // 53
  template <>
  CAttributePtr CreateAttribute< Attribute::eCustomMediaSize >( AttributeIs::Status f_Status );
  // 53
  template <>
  CAttributePtr CreateAttribute< Attribute::eDuplexPageMode >( AttributeIs::Status f_Status );
  // 54
  template <>
  CAttributePtr CreateAttribute< Attribute::eDuplexPageSide >( AttributeIs::Status f_Status );
  // 65
  template <>
  CAttributePtr CreateAttribute< Attribute::eArcDirection >( AttributeIs::Status f_Status );
  // 66
  template <>
  CAttributePtr CreateAttribute< Attribute::eBoundingBox >( AttributeIs::Status f_Status );
  // 67
  template <>
  CAttributePtr CreateAttribute< Attribute::eDashOffset >( AttributeIs::Status f_Status );
  // 68
  template <>
  CAttributePtr CreateAttribute< Attribute::eEllipseDimension >( AttributeIs::Status f_Status );
  // 69
  template <>
  CAttributePtr CreateAttribute< Attribute::eEndPoint >( AttributeIs::Status f_Status );
  // 70
  template <>
  CAttributePtr CreateAttribute< Attribute::eFillMode >( AttributeIs::Status f_Status );
  // 71
  template <>
  CAttributePtr CreateAttribute< Attribute::eLineCapStyle >( AttributeIs::Status f_Status );
  // 72
  template <>
  CAttributePtr CreateAttribute< Attribute::eLineJoinStyle >( AttributeIs::Status f_Status );
  // 73
  template <>
  CAttributePtr CreateAttribute< Attribute::eMiterLength >( AttributeIs::Status f_Status );
  // 74
  template <>
  CAttributePtr CreateAttribute< Attribute::eLineDashStyle >( AttributeIs::Status f_Status );
  // 75
  template <>
  CAttributePtr CreateAttribute< Attribute::ePenWidth >( AttributeIs::Status f_Status );
  // 76
  template <>
  CAttributePtr CreateAttribute< Attribute::ePoint >( AttributeIs::Status f_Status );
  // 77
  template <>
  CAttributePtr CreateAttribute< Attribute::eNumberOfPoints >( AttributeIs::Status f_Status );
  // 78
  template <>
  CAttributePtr CreateAttribute< Attribute::eSolidLine >( AttributeIs::Status f_Status );
  // 79
  template <>
  CAttributePtr CreateAttribute< Attribute::eStartPoint >( AttributeIs::Status f_Status );
  // 80
  template <>
  CAttributePtr CreateAttribute< Attribute::ePointType >( AttributeIs::Status f_Status );
  // 81
  template <>
  CAttributePtr CreateAttribute< Attribute::eControlPoint1 >( AttributeIs::Status f_Status );
  // 82
  template <>
  CAttributePtr CreateAttribute< Attribute::eControlPoint2 >( AttributeIs::Status f_Status );
  // 83
  template <>
  CAttributePtr CreateAttribute< Attribute::eClipRegion >( AttributeIs::Status f_Status );
  // 84
  template <>
  CAttributePtr CreateAttribute< Attribute::eClipMode >( AttributeIs::Status f_Status );

  // 98
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorDepth >( AttributeIs::Status f_Status );
  // 99
  template <>
  CAttributePtr CreateAttribute< Attribute::eBlockHeight >( AttributeIs::Status f_Status );
  // 100
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorMapping >( AttributeIs::Status f_Status );
  // 101
  template <>
  CAttributePtr CreateAttribute< Attribute::eCompressMode >( AttributeIs::Status f_Status );
  // 102
  template <>
  CAttributePtr CreateAttribute< Attribute::eDestinationBox >( AttributeIs::Status f_Status );
  // 103
  template <>
  CAttributePtr CreateAttribute< Attribute::eDestinationSize >( AttributeIs::Status f_Status );
  // 104
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternPersistence >( AttributeIs::Status f_Status );
  // 105
  template <>
  CAttributePtr CreateAttribute< Attribute::ePatternDefineID >( AttributeIs::Status f_Status );

  // 107
  template <>
  CAttributePtr CreateAttribute< Attribute::eSourceHeight >( AttributeIs::Status f_Status );
  // 108
  template <>
  CAttributePtr CreateAttribute< Attribute::eSourceWidth >( AttributeIs::Status f_Status );
  // 109
  template <>
  CAttributePtr CreateAttribute< Attribute::eStartLine >( AttributeIs::Status f_Status );
  // 110
  template <>
  CAttributePtr CreateAttribute< Attribute::ePadBytesMultiple >( AttributeIs::Status f_Status );
  // 111
  template <>
  CAttributePtr CreateAttribute< Attribute::eBlockByteLength >( AttributeIs::Status f_Status );
  //
  // 115
  template <>
  CAttributePtr CreateAttribute< Attribute::eNumberOfScanLines >( AttributeIs::Status f_Status );
  //
  // 120
  template <>
  CAttributePtr CreateAttribute< Attribute::eColorTreatment >( AttributeIs::Status f_Status );
  //
  // 129
  template <>
  CAttributePtr CreateAttribute< Attribute::eCommentData >( AttributeIs::Status f_Status );
  // 130
  template <>
  CAttributePtr CreateAttribute< Attribute::eDataOrg >( AttributeIs::Status f_Status );
  //
  // 134
  template <>
  CAttributePtr CreateAttribute< Attribute::eMeasure >( AttributeIs::Status f_Status );
  //
  // 136
  template <>
  CAttributePtr CreateAttribute< Attribute::eSourceType >( AttributeIs::Status f_Status );
  // 137
  template <>
  CAttributePtr CreateAttribute< Attribute::eUnitsPerMeasure >( AttributeIs::Status f_Status );
  //
  // 139
  template <>
  CAttributePtr CreateAttribute< Attribute::eStreamName >( AttributeIs::Status f_Status );
  // 140
  template <>
  CAttributePtr CreateAttribute< Attribute::eStreamDataLength >( AttributeIs::Status f_Status );
  //
  // 143
  template <>
  CAttributePtr CreateAttribute< Attribute::eErrorReport >( AttributeIs::Status f_Status );
  //
  // 145
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUExtension >( AttributeIs::Status f_Status );
  // 146
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUDataLength >( AttributeIs::Status f_Status );
  // 147
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr1 >( AttributeIs::Status f_Status );
  // 148
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr2 >( AttributeIs::Status f_Status );
  // 149
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr3 >( AttributeIs::Status f_Status );
  // 150
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr4 >( AttributeIs::Status f_Status );
  // 151
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr5 >( AttributeIs::Status f_Status );
  // 152
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr6 >( AttributeIs::Status f_Status );
  // 153
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr7 >( AttributeIs::Status f_Status );
  // 154
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr8 >( AttributeIs::Status f_Status );
  // 155
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr9 >( AttributeIs::Status f_Status );
  // 156
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr10 >( AttributeIs::Status f_Status );
  // 157
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr11 >( AttributeIs::Status f_Status );
  // 158
  template <>
  CAttributePtr CreateAttribute< Attribute::eVUAttr12 >( AttributeIs::Status f_Status );
  //
  // 161
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharAngle >( AttributeIs::Status f_Status );
  // 162
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharCode >( AttributeIs::Status f_Status );
  // 163
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharDataSize >( AttributeIs::Status f_Status );
  // 164
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharScale >( AttributeIs::Status f_Status );
  // 165
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharShear >( AttributeIs::Status f_Status );
  // 166
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharSize >( AttributeIs::Status f_Status );
  // 167
  template <>
  CAttributePtr CreateAttribute< Attribute::eFontHeaderLength >( AttributeIs::Status f_Status );
  // 168
  template <>
  CAttributePtr CreateAttribute< Attribute::eFontName >( AttributeIs::Status f_Status );
  // 169
  template <>
  CAttributePtr CreateAttribute< Attribute::eFontFormat >( AttributeIs::Status f_Status );
  // 170
  template <>
  CAttributePtr CreateAttribute< Attribute::eSymbolSet >( AttributeIs::Status f_Status );
  // 171
  template <>
  CAttributePtr CreateAttribute< Attribute::eTextData >( AttributeIs::Status f_Status );
  // 172
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharSubModeArray >( AttributeIs::Status f_Status );
  //
  // 175
  template <>
  CAttributePtr CreateAttribute< Attribute::eXSpacingData >( AttributeIs::Status f_Status );
  // 176
  template <>
  CAttributePtr CreateAttribute< Attribute::eYSpacingData >( AttributeIs::Status f_Status );
  // 177
  template <>
  CAttributePtr CreateAttribute< Attribute::eCharBoldValue >( AttributeIs::Status f_Status );



};

#endif /* __CREATEATTRIBUTE_HPP__ */
