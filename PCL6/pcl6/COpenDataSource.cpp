//*****************************************************************************
//        File: COpenDataSource.cpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "COpenDataSource.hpp"


namespace pcl6 {
//******************************************************************************
  COpenDataSource::COpenDataSource() : CPclOperator( PclTag::eOpenDataSource ),
    pvSourceType( CreateAttribute< Attribute::eSourceType >( AttributeIs::Obligatory ) ),
    pvDataOrg( CreateAttribute< Attribute::eDataOrg >( AttributeIs::Obligatory ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  COpenDataSource::~COpenDataSource() {
  }
//******************************************************************************
  bool COpenDataSource::SetAttributes( const CAttributeArray& f_Atributes ) {
    return  ptSetAttributes( f_Atributes,
        &pvSourceType,
        &pvDataOrg,
        0L );
  }
//******************************************************************************
  bool COpenDataSource::IsValid() const{
    return  pvSourceType->IsValid() && pvDataOrg->IsValid();
  }
//******************************************************************************
  CAttributePtr& COpenDataSource::SourceType(){
    return pvSourceType;
  }
//******************************************************************************
  const CAttributePtr& COpenDataSource::SourceType() const{
    return pvSourceType;
  }
//******************************************************************************
  CAttributePtr& COpenDataSource::DataOrg(){
    return pvDataOrg;
  }
//******************************************************************************
  const CAttributePtr& COpenDataSource::DataOrg() const{
    return pvDataOrg;
  }

}
