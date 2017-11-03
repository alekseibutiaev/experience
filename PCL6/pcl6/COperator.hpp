//*****************************************************************************
//        File: COperator.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CPERATOR_HPP__
#define __CPERATOR_HPP__

#include <vector>
#include <utility>
#include <boost/smart_ptr.hpp>

#include "CAttribute.hpp"
#include "CTag.hpp"

namespace pcl6 {

  class COperator;

  typedef boost::shared_ptr< COperator > COperatorPtr;
  typedef std::vector< COperatorPtr > COperatorsArray;

  class COperator : public CBaseTag {
  public:
    virtual ~COperator();
    virtual bool IsValid() const = 0;
  protected:
    COperator( const int& f_Tag );
  };

}; /* namespace pcl6 */

#endif /* __COPERATOR_HPP__ */
