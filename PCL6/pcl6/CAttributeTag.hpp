//*****************************************************************************
//        File: CAttributeTag.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CATTRIBUTETAG_HPP__
#define __CATTRIBUTETAG_HPP__

#include <iostream>

#include "CValueType.hpp"
#include "CAttribute.hpp"
#include "AttributeID.hpp"
#include "StaticIf.hpp"

namespace pcl6 {

  typedef CValueType< Value::eUbyte > CByte;
  typedef CValueType< Value::eUint16 > CWord;

  template < int ATTRTAG >
  class CAttributeTag : public CAttribute {
  public:
    CAttributeTag( AttributeIs::Status f_Status = AttributeIs::Obligatory,
        Attribute::ID f_AttributeId = Attribute::eInvalidID ) :
      CAttribute( ATTRTAG, f_Status ), pvAttributeID( f_AttributeId ) {
    }
    ~CAttributeTag() {
    }
    bool SetAttributeID( FileIperator& f_Begin, const FileIperator& f_End ) {
      return SetValue( f_Begin, f_End, pvAttributeID );
    }
    int AttributeID() const {
      return pvAttributeID;
    }
  private:
    typedef typename if_c< ATTRTAG == AttributeTag::eAttr8,
      CByte, CWord >::type::value_type CAttributeId;
    CAttributeId pvAttributeID;
    AttributeIs::Status pvStatus;
    CDataTypePtr pvData;
  };

}

#endif /* CATTRIBUTETAG_HPP_ */
