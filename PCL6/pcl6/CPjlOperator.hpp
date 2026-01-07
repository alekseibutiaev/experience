//*****************************************************************************
//        File: CPjlOperator.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CPJLOPERATOR_HPP__
#define __CPJLOPERATOR_HPP__

#include <string>
#include <boost/smart_ptr.hpp>
#include "COperator.hpp"

namespace pcl6 {

  namespace PjlTag {
    enum TAG{
      eHeader             = 0x1B,   // PJL operators
      eStreamHeader       = 0x29,   // PJL operators
      ePJL                = 0x40,   // PJL operators
    };
  } /* namespace PjlTag */
//******************************************************************************
  class CPjlOperator;
  typedef boost::shared_ptr< CPjlOperator > CPjlOperatorPtr;
//******************************************************************************
  class CPjlOperator : public COperator {
  public:
    CPjlOperator( const Byte& f_OperatorTag );
    ~CPjlOperator();
    static CPjlOperatorPtr Create( const Byte& f_Tag );
    bool IsValid() const;
    bool SetString( FileIperator& f_Begin, const FileIperator& f_End );
    std::string Command() const;
    std::string Parameter() const;
    std::string Value() const;
  private:
    mutable bool pvHaveBeenParsed;
    std::string pvPjlString;
    mutable std::string pvCommand;
    mutable std::string pvParameter;
    mutable std::string pvValue;
  };


}; /* namespace pcl6 */

#endif /* __CPJLOPERATOR_HPP__ */
