//*****************************************************************************
//        File: CEmbedType.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CEMBEDTYPE_HPP__
#define __CEMBEDTYPE_HPP__

#include <boost/smart_ptr.hpp>

#include "COperator.hpp"

namespace pcl6 {

  namespace EmbedData {
    enum TYPE {
      eDataLength  = 0xfa,
      eDataLengthByte  = 0xfb,
    };
  }; /* namespace EmbedData */
//*****************************************************************************
  class CEmbedType;
  typedef boost::shared_ptr< CEmbedType >CEmbedTypePtr;
//*****************************************************************************

  class CEmbedType : public COperator {
  public:
    virtual ~CEmbedType();
    static CEmbedTypePtr Create( const Byte& f_Tag );
    virtual bool ReadData( FileIperator& f_Begin, const FileIperator& f_End ) = 0;
    virtual const std::size_t Size() const = 0;
  protected:
    CEmbedType( const Byte& f_Tag );
  };

}; /* namespace pcl6 */

#endif /* __CEMBEDTYPE_HPP__ */
