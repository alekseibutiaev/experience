/*
 * PCL6AttributeID.hpp
 *
 *  Created on: 26.11.2009
 *      Author: alexsy
 */

#ifndef __PCL6ATTRIBUTEID_HPP__
#define __PCL6ATTRIBUTEID_HPP__

namespace pcl6 {

  typedef enum {
    eClockWise = 0,
    eCounterClockWise,
    pxeArcDirection_next
  } EArcDirection;

  typedef enum {
    eNoSubstitution = 0,
    eVerticalSubstitution,
    pxeCharSubModeArray_next
  } ECharSubModeArray;

  typedef enum {
    eNonZeroWinding = 0,
    eEvenOdd,
    pxeClipMode_next,
    pxeFillMode_next = pxeClipMode_next		/* see pxeFillMode below */
  } EClipMode;

  typedef enum {
    eInterior = 0,
    eExterior,
    pxeClipRegion_next
  } EClipRegion;

  typedef enum {
    e1Bit = 0,
    e4Bit,
    e8Bit,
    pxeColorDepth_next
  } EColorDepth;

  typedef enum {
    eCRGB = 5,			/* Note: for this enumeration, 0 is not a valid value */
    pxeColorimetricColorSpace_next
  } EColorimetricColorSpace;	/* 2.0 */

  typedef enum {
    eDirectPixel = 0,
    eIndexedPixel,
    pxeColorMapping_next
  } EColorMapping;

  typedef enum {
    eNoColorSpace = 0,		/* Note: for this enumeration, 0 is not a valid value */
    eGray,
    eRGB,
    eSRGB = 6,		/* 2.0, Note: HP's value is 6 not the expected 3 */
    pxeColorSpace_next
  } EColorSpace;

  typedef enum {
    eNoCompression = 0,
    eRLECompression,
    eJPEGCompression,		/* 2.0 */
    eDeltaRowCompression,       /* 2.1 */
    pxeCompressMode_next
  } ECompressMode;

  typedef enum {
    eBinaryHighByteFirst = 0,
    eBinaryLowByteFirst,
    pxeDataOrg_next		/* is this DataOrg or DataOrganization? */
  } EDataOrg;

  typedef enum {
    eDefault = 0,		/* bad choice of name! */
    pxeDataSource_next
  } EDataSource;

  typedef enum {
    eUByte = 0,
    eSByte,
    eUInt16,
    eSInt16,
    pxeDataType_next
  } EDataType;

  typedef enum {
    eDownloaded = -1,		/* Not a real value, indicates a downloaded matrix */
    eDeviceBest = 0,
    pxeDitherMatrix_next
  } EDitherMatrix;

  typedef enum {
    eDuplexHorizontalBinding = 0,
    eDuplexVerticalBinding,
    pxeDuplexPageMode_next
  } EDuplexPageMode;

  typedef enum {
    eFrontMediaSide = 0,
    eBackMediaSide,
    pxeDuplexPageSide_next
  } EDuplexPageSide;

  typedef enum {
    /* Several pieces of code know that this is a bit mask. */
    eNoReporting = 0,
    eBackChannel,
    eErrorPage,
    eBackChAndErrPage,
    eNWBackChannel,		/* 2.0 */
    eNWErrorPage,		/* 2.0 */
    eNWBackChAndErrPage,	/* 2.0 */
    pxeErrorReport_next
  } EErrorReport;

  typedef EClipMode EFillMode;

  typedef enum {
    eButtCap = 0,
    eRoundCap,
    eSquareCap,
    eTriangleCap,
    pxeLineCap_next
  } ELineCap;

  #define ELineCap_to_library\
    { gs_cap_butt, gs_cap_round, gs_cap_square, gs_cap_triangle }

  typedef enum {
    eMiterJoin = 0,
    eRoundJoin,
    eBevelJoin,
    eNoJoin,
    pxeLineJoin_next
  } ELineJoin;

  #define pxeLineJoin_to_library\
    { gs_join_miter, gs_join_round, gs_join_bevel, gs_join_none }

  typedef enum {
    eInch = 0,
    eMillimeter,
    eTenthsOfAMillimeter,
  } EMeasure;

  #define pxeMeasure_to_points { 72.0, 72.0 / 25.4, 72.0 / 254.0 }

  typedef enum {
    eDefaultDestination = 0,
    eFaceDownBin,		/* 2.0 */
    eFaceUpBin,			/* 2.0 */
    eJobOffsetBin,		/* 2.0 */
    pxeMediaDestination_next
  } EMediaDestination;

  typedef enum {
    eLetterPaper = 0,
    eLegalPaper,
    eA4Paper,
    eExecPaper,
    eLedgerPaper,
    eA3Paper,
    eCOM10Envelope,
    eMonarchEnvelope,
    eC5Envelope,
    eDLEnvelope,
    eJB4Paper,
    eJB5Paper,
    eB5Envelope,
    eB5Paper,                 /* 2.1 */
    eJPostcard,
    eJDoublePostcard,
    eA5Paper,
    eA6Paper,                 /* 2.0 */
    eJB6Paper,                /* 2.0 */
    eJIS8K,                   /* 2.1 */
    eJIS16K,                  /* 2.1 */
    eJISExec,                 /* 2.1 */
    eDefaultPaperSize = 96,   /* 2.1 */
    pxeMediaSize_next
  } EMediaSize;

/*
 * Apply a macro (or procedure) to all known paper sizes.
 * The arguments are:
 *      media size code, resolution for width/height, width, height.
 * NB - todo ( -1, -1, -1 ) see below.
 */
#define px_enumerate_media(m)\
  m(eDefaultPaperSize, -1, -1, -1)\
  m(eLetterPaper, 300, 2550, 3300)\
  m(eLegalPaper, 300, 2550, 5300)\
  m(eA4Paper, 300, 2480, 3507)\
  m(eExecPaper, 300, 2175, 3150)\
  m(eLedgerPaper, 300, 3300, 5100)\
  m(eA3Paper, 300, 3507, 4960)\
  m(eCOM10Envelope, 300, 1237, 2850)\
  m(eMonarchEnvelope, 300, 1162, 2250)\
  m(eC5Envelope, 300, 1913, 2704)\
  m(eDLEnvelope, 300, 1299, 2598)\
  m(eJB4Paper, -1, -1, -1)\
  m(eJB5Paper, -1, -1, -1)\
  m(eB5Envelope, 300, 2078, 2952)\
  m(eB5Paper, -1, -1, -1)\
  m(eJPostcard,  -1, -1, -1)\
  m(eJDoublePostcard, -1, -1, -1)\
  m(eA5Paper,-1, -1, -1)\
  m(eA6Paper,-1, -1, -1)\
  m(eJB6Paper,-1, -1, -1)\
  m(eJIS8K, -1, -1, -1)\
  m(eJIS16K, -1, -1, -1)\
  m(eJISExec, -1, -1, -1)

  typedef enum {
    eDefaultSource = 0,
    eAutoSelect,
    eManualFeed,
    eMultiPurposeTray,
    eUpperCassette,
    eLowerCassette,
    eEnvelopeTray,
    eThirdCassette,
    pxeMediaSource_next
  } EMediaSource;

/**** MediaType is not documented. ****/
  typedef enum {
    eDefaultType = 0,
    pxeMediaType_next
  } EMediaType;

  typedef enum {
    ePortraitOrientation = 0,
    eLandscapeOrientation,
    eReversePortrait,
    eReverseLandscape,
    eDefaultOrientation, /* 2.1 */
    pxeOrientation_next
  } EOrientation;

  typedef enum {
    eTempPattern = 0,
    ePagePattern,
    eSessionPattern,
    pxePatternPersistence_next
  } EPatternPersistence;

  typedef enum {
    eSimplexFrontSide = 0,
    pxeSimplexPageMode_next
  } ESimplexPageMode;

  typedef enum {
    eOpaque = 0,
    eTransparent,
    pxeTxMode_next
  } ETxMode;

  typedef enum {
    eHorizontal = 0,
    eVertical,
    pxeWritingMode_next
  } EWritingMode;		/* 2.0 */

/* the following 4 enumerations are new with XL 3.0 */

  typedef enum {
    eDisableAH = 0,   /* the documentation uses a eDisable here and in
                         Trapping - add AH to avoid duplicate
                         identifier. */
    eEnableAH,
    pxeAdaptive_Halftoning_next
  } EAdaptiveHalftone;

  typedef enum {
    eHighLPI = 0,
    eMediumLPI,
    eLowLPI,
    pxeeHalftoneMethod_next
  } EHalftoneMethod;

  typedef enum {
    eDisableCT = 0,
    eMax,
    eNormal,
    eLight,
    pxeColorTrapping_next
  } EColorTrapping;

  typedef enum {
    eTonerBlack = 0,
    eProcessBlack,
    pxeNeutralAxis_next
  } ENeutralAxis;

  typedef enum {
    eNoTreatment = 0,
    eScreenMatch,
    eVivid,
    pxeColorTreatment_next
  } EColorTreatment;

  namespace Attribute {
    enum ID{
      //
      ePaletteDepth = 2,
      eColorSpace = 3,
      eNullBrush = 4,
      eNullPen = 5,
      ePaletteData = 6,
      //
      ePatternSelectID = 8,
      eGrayLevel = 9,
      //
      eRGBColor = 11,
      ePatternOrigin = 12,
      eNewDestinationSize = 13,
      ePrimaryArray = 14,
      ePrimaryDepth = 15,
      //
      eDeviceMatrix = 33,
      eDitherMatrixDataType = 34,
      eDitherOrigin = 35,
      eMediaDestination = 36,
      eMediaSize = 37,
      eMediaSource = 38,
      eMediaType = 39,
      eOrientation = 40,
      ePageAngle = 41,
      ePageOrigin = 42,
      ePageScale = 43,
      eROP3 = 44,
      eTxMode = 45,
      //
      eCustomMediaSize = 47,
      eCustomMediaSizeUnits = 48,
      ePageCopies = 49,
      eDitherMatrixSize = 50,
      eDitherMatrixDepth = 51,
      eSimplexPageMode = 52,
      eDuplexPageMode = 53,
      eDuplexPageSide = 54,
      //
      eArcDirection = 65,
      eBoundingBox = 66,
      eDashOffset = 67,
      eEllipseDimension = 68,
      eEndPoint = 69,
      eFillMode = 70,
      eLineCapStyle = 71,
      eLineJoinStyle = 72,
      eMiterLength = 73,
      eLineDashStyle = 74,
      ePenWidth = 75,
      ePoint = 76,
      eNumberOfPoints = 77,
      eSolidLine = 78,
      eStartPoint = 79,
      ePointType = 80,
      eControlPoint1 = 81,
      eControlPoint2 = 82,
      eClipRegion = 83,
      eClipMode = 84,
      //
      eColorDepth = 98,
      eBlockHeight = 99,
      eColorMapping = 100,
      eCompressMode = 101,
      eDestinationBox = 102,
      eDestinationSize = 103,
      ePatternPersistence = 104,
      ePatternDefineID = 105,
      //
      eSourceHeight = 107,
      eSourceWidth = 108,
      eStartLine = 109,
      ePadBytesMultiple = 110,
      eBlockByteLength = 111,
      //
      eNumberOfScanLines = 115,
      //
      eColorTreatment = 120,
      //
      eCommentData = 129,
      eDataOrg = 130,
      //
      eMeasure = 134,
      //
      eSourceType = 136,
      eUnitsPerMeasure = 137,
      //
      eStreamName = 139,
      eStreamDataLength = 140,
      //
      eErrorReport = 143,
      //
      eVUExtension = 145,  /* \                                             */
      eVUDataLength = 146, /* |                                             */
      eVUAttr1 = 147,      /* |                                             */
      eVUAttr2 = 148,      /* |                                             */
      eVUAttr3 = 149,      /* |                                             */
      eVUAttr4 = 150,      /* |                                             */
      eVUAttr5 = 151,      /*  \                                            */
      eVUAttr6 = 152,      /*   >  Not documentary attribute                */
      eVUAttr7 = 153,      /*  /                                            */
      eVUAttr8 = 154,      /* |                                             */
      eVUAttr9 = 155,      /* |                                             */
      eVUAttr10 = 156,     /* |                                             */
      eVUAttr11 = 157,     /* |                                             */
      eVUAttr12 = 158,     /* /                                             */
      //
      eCharAngle = 161,
      eCharCode = 162,
      eCharDataSize = 163,
      eCharScale = 164,
      eCharShear = 165,
      eCharSize = 166,
      eFontHeaderLength = 167,
      eFontName = 168,
      eFontFormat = 169,
      eSymbolSet = 170,
      eTextData = 171,
      eCharSubModeArray = 172,
      //
      eXSpacingData = 175,
      eYSpacingData = 176,
      eCharBoldValue = 177,
      eInvalidID = 256
    };

  }; /* namespace AttributeID */

}; /* namespace pcl6 */

#endif /* __PCL6ATTRIBUTEID_HPP__ */
