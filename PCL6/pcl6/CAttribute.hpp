//*****************************************************************************
//        File: CAttribute.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef CATTRIBUTE_HPP_
#define CATTRIBUTE_HPP_

#include <vector>
#include <boost/smart_ptr.hpp>

#include "CTag.hpp"
#include "CDataType.hpp"

namespace pcl6 {

  namespace AttributeIs {
    enum Status {
      Optional = 0,
      Obligatory = 1
    };
  };

  namespace AttributeTag {
    typedef enum {
      eAttr8 = 0xf8,
      eAttr16 = 0xf9
    } EAttributeSize;
  }

  class CAttribute;
  typedef boost::shared_ptr< CAttribute > CAttributePtr;
  typedef std::vector< CAttributePtr > CAttributeArray;


  class CAttribute : public CBaseTag {
  public:
    ~CAttribute();

    CDataTypePtr& Data();
    const CDataTypePtr& Data() const;
    bool IsValid() const;
    bool IsSet() const;

    virtual bool SetAttributeID( FileIperator& f_Begin, const FileIperator& f_End ) = 0;
    virtual int AttributeID() const = 0;

    static CAttributePtr Create( const Byte& f_AttributeTag,
        AttributeIs::Status f_Status = AttributeIs::Obligatory );
  protected:
    CAttribute( const int& f_Tag, AttributeIs::Status f_Status );
  private:
    AttributeIs::Status pvStatus;
    CDataTypePtr pvData;
  };

}

#endif /* CATTRIBUTE_HPP_ */
