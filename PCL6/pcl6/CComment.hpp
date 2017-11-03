//*****************************************************************************
//        File: CComment.hpp
//     Project: kopirkin
//  Created on: 05.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CCOMMENT_HPP__
#define __CCOMMENT_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {

  class CComment : public CPclOperator {
  public:
    CComment();
    ~CComment();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& CommentData();
    const CAttributePtr& CommentData() const;
  private:
    CAttributePtr pvCommentData;
  };

}

#endif /* __CCOMMENT_HPP__ */
