//*****************************************************************************
//        File: CComment.cpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CComment.hpp"

namespace pcl6 {
//******************************************************************************
  CComment::CComment() : CPclOperator( PclTag::eComment ),
    pvCommentData( CreateAttribute< Attribute::eCommentData >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CComment::~CComment() {
  }
//******************************************************************************
  bool CComment::SetAttributes(
      const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvCommentData,
        0L );
  }
//******************************************************************************
  bool CComment::IsValid() const{
    return pvCommentData->IsValid();
  }
//******************************************************************************
  CAttributePtr& CComment::CommentData(){
    return this->pvCommentData;
  }
//******************************************************************************
  const CAttributePtr& CComment::CommentData() const{
    return this->pvCommentData;
  }

}
