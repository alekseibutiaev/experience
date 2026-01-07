//*****************************************************************************
//        File: COpenDataSource.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef COPENDATASOURCE_HPP_
#define COPENDATASOURCE_HPP_

#include "CAttribute.hpp"
#include "CPclOperator.hpp"


namespace pcl6 {

  class COpenDataSource : public CPclOperator {
  public:
    COpenDataSource();
    ~COpenDataSource();
    bool SetAttributes( const CAttributeArray& f_Atributes );;
    bool IsValid() const;
    CAttributePtr& SourceType();
    const CAttributePtr& SourceType() const;
    CAttributePtr& DataOrg();
    const CAttributePtr& DataOrg() const;
  private:
    CAttributePtr pvSourceType;
    CAttributePtr pvDataOrg;
  };

}

#endif /* COPENDATASOURCE_HPP_ */
