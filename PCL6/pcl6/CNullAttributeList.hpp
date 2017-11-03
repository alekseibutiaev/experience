//*****************************************************************************
//        File: CNullAttributeList.hpp
//  Created on: 01.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CNULLATTRIBUTELIST_HPP__
#define __CNULLATTRIBUTELIST_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CNullAttributeList : public CPclOperator {
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
  protected:
    CNullAttributeList( const int& f_Tag );
    ~CNullAttributeList();
  };
//******************************************************************************
// CEndSession
//******************************************************************************
  class CEndSession : public CNullAttributeList {
  public:
    CEndSession();
    ~CEndSession();
  };
//******************************************************************************
// CCloseDataSource
//******************************************************************************
  class CCloseDataSource : public CNullAttributeList {
  public:
    CCloseDataSource();
    ~CCloseDataSource();
  };
//******************************************************************************
// CEndFontHeader
//******************************************************************************
  class CEndFontHeader : public CNullAttributeList {
  public:
    CEndFontHeader();
    ~CEndFontHeader();
  };
//******************************************************************************
// CEndChar
//******************************************************************************
  class CEndChar : public CNullAttributeList {
  public:
    CEndChar();
    ~CEndChar();
  };
//******************************************************************************
// CEndStream
//******************************************************************************
  class CEndStream : public CNullAttributeList {
  public:
    CEndStream();
    ~CEndStream();
  };
//******************************************************************************
// CPopGS
//******************************************************************************
  class CPopGS : public CNullAttributeList {
  public:
    CPopGS();
    ~CPopGS();
  };
//******************************************************************************
// CPushGS
//******************************************************************************
  class CPushGS : public CNullAttributeList {
  public:
    CPushGS();
    ~CPushGS();
  };
//******************************************************************************
// CSetClipToPage
//******************************************************************************
  class CSetClipToPage : public CNullAttributeList {
  public:
    CSetClipToPage();
    ~CSetClipToPage();
  };
//******************************************************************************
// CSetPageDefaultCTM
//******************************************************************************
  class CSetPageDefaultCTM : public CNullAttributeList {
  public:
    CSetPageDefaultCTM();
    ~CSetPageDefaultCTM();
  };
//******************************************************************************
// CSetPathToClip
//******************************************************************************
  class CSetPathToClip : public CNullAttributeList {
  public:
    CSetPathToClip();
    ~CSetPathToClip();
  };
//******************************************************************************
// CCloseSubPath
//******************************************************************************
  class CCloseSubPath : public CNullAttributeList {
  public:
    CCloseSubPath();
    ~CCloseSubPath();
  };
//******************************************************************************
// CNewPath
//******************************************************************************
  class CNewPath : public CNullAttributeList {
  public:
    CNewPath();
    ~CNewPath();
  };
//******************************************************************************
// CPaintPath
//******************************************************************************
  class CPaintPath : public CNullAttributeList {
  public:
    CPaintPath();
    ~CPaintPath();
  };
//******************************************************************************
// CEndImage
//******************************************************************************
  class CEndImage : public CNullAttributeList {
  public:
    CEndImage();
    ~CEndImage();
  };
//******************************************************************************
// CEndRastPattern
//******************************************************************************
  class CEndRastPattern : public CNullAttributeList {
  public:
    CEndRastPattern();
    ~CEndRastPattern();
  };
//******************************************************************************
// CBeginScan
//******************************************************************************
  class CBeginScan : public CNullAttributeList {
  public:
    CBeginScan();
    ~CBeginScan();
  };
//******************************************************************************
// CEndScan
//******************************************************************************
  class CEndScan : public CNullAttributeList {
  public:
    CEndScan();
    ~CEndScan();
  };

}

#endif /* __CNULLATTRIBUTELIST_HPP__ */


