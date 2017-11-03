//*****************************************************************************
//        File: CDataType.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CDATATYPE_HPP__
#define __CDATATYPE_HPP__

#include <vector>
#include <boost/smart_ptr.hpp>

#include "CTag.hpp"

namespace pcl6 {

  class CDataType;

  typedef boost::shared_ptr< CDataType > CDataTypePtr;

  class CDataType : public CBaseTag {
  public:
    virtual bool SetData( FileIperator& f_Begin, const FileIperator& f_End ) = 0;
    static CDataTypePtr Create( const Byte& f_DataType );
    virtual std::size_t AsInteger() const;
    virtual ~CDataType();
  protected:
    CDataType( const int& f_Tag );
  };

}

#endif /* __CDATATYPE_HPP__ */
