//*****************************************************************************
//        File: CVendorUnique.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __CVENDORUNIQUE_HPP__
#define __CVENDORUNIQUE_HPP__

#include "CAttribute.hpp"
#include "CPclOperator.hpp"

namespace pcl6 {
//******************************************************************************
  class CVendorUnique : public CPclOperator {
  public:
    CVendorUnique();
    ~CVendorUnique();
    bool SetAttributes( const CAttributeArray& f_Atributes );
    bool IsValid() const;
    CAttributePtr& VUExtension();
    const CAttributePtr& VUExtension() const;
    CAttributePtr& VUDataLength();
    const CAttributePtr& VUDataLength() const;
    CAttributePtr& VUAttr1();
    const CAttributePtr& VUAttr1() const;
    CAttributePtr& VUAttr2();
    const CAttributePtr& VUAttr2() const;
    CAttributePtr& VUAttr3();
    const CAttributePtr& VUAttr3() const;
    CAttributePtr& VUAttr4();
    const CAttributePtr& VUAttr4() const;
    CAttributePtr& VUAttr5();
    const CAttributePtr& VUAttr5() const;
    CAttributePtr& VUAttr6();
    const CAttributePtr& VUAttr6() const;
    CAttributePtr& VUAttr7();
    const CAttributePtr& VUAttr7() const;
    CAttributePtr& VUAttr8();
    const CAttributePtr& VUAttr8() const;
    CAttributePtr& VUAttr9();
    const CAttributePtr& VUAttr9() const;
    CAttributePtr& VUAttr10();
    const CAttributePtr& VUAttr10() const;
    CAttributePtr& VUAttr11();
    const CAttributePtr& VUAttr11() const;
    CAttributePtr& VUAttr12();
    const CAttributePtr& VUAttr12() const;
  private:
    CAttributePtr pvVUExtension;
    CAttributePtr pvVUDataLength;
    CAttributePtr pvVUAttr1;
    CAttributePtr pvVUAttr2;
    CAttributePtr pvVUAttr3;
    CAttributePtr pvVUAttr4;
    CAttributePtr pvVUAttr5;
    CAttributePtr pvVUAttr6;
    CAttributePtr pvVUAttr7;
    CAttributePtr pvVUAttr8;
    CAttributePtr pvVUAttr9;
    CAttributePtr pvVUAttr10;
    CAttributePtr pvVUAttr11;
    CAttributePtr pvVUAttr12;
  };


}; /* namespace pcl6 */

#endif /* __CVENDORUNIQUE_HPP__ */
