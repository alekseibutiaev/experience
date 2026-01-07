//*****************************************************************************
//        File: CEndPage.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CEndPage.hpp"

namespace pcl6 {
//******************************************************************************
  CEndPage::CEndPage() : CPclOperator( PclTag::eEndPage ),
    pvPageCopies( CreateAttribute< Attribute::ePageCopies >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CEndPage::~CEndPage() {
  }
//******************************************************************************
  bool CEndPage::SetAttributes( const CAttributeArray& f_Atributes ){
    return ptSetAttributes( f_Atributes,
        &pvPageCopies,
        0L );
  }
//******************************************************************************
  bool CEndPage::IsValid() const{
    return pvPageCopies->IsValid();
  }
//******************************************************************************
  CAttributePtr& CEndPage::PageCopies(){
    return this->pvPageCopies;
  }
//******************************************************************************
  const CAttributePtr& CEndPage::PageCopies() const{
    return this->pvPageCopies;
  }

}
