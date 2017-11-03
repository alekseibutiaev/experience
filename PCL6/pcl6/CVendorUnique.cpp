//*****************************************************************************
//        File: CVendorUnique.hpp
//     Project: kopirkin
//  Created on: 03.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include "CreateAttribute.hpp"
#include "CVendorUnique.hpp"

namespace pcl6 {

//******************************************************************************
  CVendorUnique::CVendorUnique() : CPclOperator( PclTag::eVendorUnique ),
    pvVUExtension( CreateAttribute< Attribute::eVUExtension >( AttributeIs::Obligatory ) ),
    pvVUDataLength( CreateAttribute< Attribute::eVUDataLength >( AttributeIs::Optional ) ),
    pvVUAttr1( CreateAttribute< Attribute::eVUAttr1 >( AttributeIs::Obligatory ) ),
    pvVUAttr2( CreateAttribute< Attribute::eVUAttr2 >( AttributeIs::Optional ) ),
    pvVUAttr3( CreateAttribute< Attribute::eVUAttr3 >( AttributeIs::Optional ) ),
    pvVUAttr4( CreateAttribute< Attribute::eVUAttr4 >( AttributeIs::Optional ) ),
    pvVUAttr5( CreateAttribute< Attribute::eVUAttr5 >( AttributeIs::Optional ) ),
    pvVUAttr6( CreateAttribute< Attribute::eVUAttr6 >( AttributeIs::Optional ) ),
    pvVUAttr7( CreateAttribute< Attribute::eVUAttr7 >( AttributeIs::Optional ) ),
    pvVUAttr8( CreateAttribute< Attribute::eVUAttr8 >( AttributeIs::Optional ) ),
    pvVUAttr9( CreateAttribute< Attribute::eVUAttr9 >( AttributeIs::Optional ) ),
    pvVUAttr10( CreateAttribute< Attribute::eVUAttr10 >( AttributeIs::Optional ) ),
    pvVUAttr11( CreateAttribute< Attribute::eVUAttr11 >( AttributeIs::Optional ) ),
    pvVUAttr12( CreateAttribute< Attribute::eVUAttr12 >( AttributeIs::Optional ) )
  {
    OPERATOR_NAME;
  }
//******************************************************************************
  CVendorUnique::~CVendorUnique() {
  }
//******************************************************************************
  bool CVendorUnique::SetAttributes( const CAttributeArray& f_Atributes ) {
    return ptSetAttributes( f_Atributes,
        &pvVUExtension,
        &pvVUDataLength,
        &pvVUAttr1,
        &pvVUAttr2,
        &pvVUAttr3,
        &pvVUAttr4,
        &pvVUAttr5,
        &pvVUAttr6,
        &pvVUAttr7,
        &pvVUAttr8,
        &pvVUAttr9,
        &pvVUAttr10,
        &pvVUAttr11,
        &pvVUAttr12,
        0L );
  }
//******************************************************************************
  bool CVendorUnique::IsValid() const{
    return pvVUDataLength->IsValid() && pvVUAttr1->IsValid() &&
      pvVUAttr2->IsValid() && pvVUAttr3->IsValid() &&
      pvVUAttr4->IsValid() && pvVUAttr5->IsValid() &&
      pvVUAttr6->IsValid() && pvVUAttr7->IsValid() &&
      pvVUAttr8->IsValid() && pvVUAttr9->IsValid() &&
      pvVUAttr10->IsValid() && pvVUAttr11->IsValid() &&
      pvVUAttr12->IsValid();

  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUExtension(){
    return this->pvVUExtension;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUExtension() const{
    return this->pvVUExtension;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUDataLength(){
    return this->pvVUDataLength;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUDataLength() const {
    return this->pvVUDataLength;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr1(){
    return this->pvVUAttr1;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr1()  const{
    return this->pvVUAttr1;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr2(){
    return this->pvVUAttr2;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr2()  const{
    return this->pvVUAttr2;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr3(){
    return this->pvVUAttr3;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr3()  const{
    return this->pvVUAttr3;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr4(){
    return this->pvVUAttr4;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr4()  const{
    return this->pvVUAttr4;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr5(){
    return this->pvVUAttr5;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr5()  const{
    return this->pvVUAttr5;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr6(){
    return this->pvVUAttr6;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr6()  const{
    return this->pvVUAttr6;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr7(){
    return this->pvVUAttr7;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr7()  const{
    return this->pvVUAttr7;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr8(){
    return this->pvVUAttr8;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr8()  const{
    return this->pvVUAttr8;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr9(){
    return this->pvVUAttr9;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr9()  const{
    return this->pvVUAttr9;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr10(){
    return this->pvVUAttr10;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr10()  const{
    return this->pvVUAttr10;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr11(){
    return this->pvVUAttr11;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr11()  const{
    return this->pvVUAttr11;
  }
//******************************************************************************
  CAttributePtr& CVendorUnique::VUAttr12(){
    return this->pvVUAttr12;
  }
//******************************************************************************
  const CAttributePtr& CVendorUnique::VUAttr12()  const{
    return this->pvVUAttr12;
  }

}; /* namespace pcl6 */
