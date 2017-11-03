//*****************************************************************************
//        File: ParserFunction.hpp
//     Project: kopirkin
//  Created on: 04.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __PARSERFUNCTION_HPP__
#define __PARSERFUNCTION_HPP__

#include "Common.hpp"
#include "CDataType.hpp"
#include "CAttribute.hpp"
#include "CEmbedData.hpp"
#include "CPclOperator.hpp"
#include "CPjlOperator.hpp"

namespace pcl6 {


  bool ReadData( FileIperator& f_Begin, const FileIperator& f_End,
      CDataTypePtr& f_Result );
  bool ReadAttribute( FileIperator& f_Begin, const FileIperator& f_End,
      CAttributePtr& f_Result );
  bool ReadPcl( FileIperator& f_Begin, const FileIperator& f_End,
      CAttributeArray& f_Attribute, COperatorPtr& f_Result );
  bool ReadPjl( FileIperator& f_Begin, const FileIperator& f_End,
      COperatorPtr& f_Result );
  bool ReadEmbedData( FileIperator& f_Begin, const FileIperator& f_End,
      COperatorPtr& f_Result );

  bool ReadFile( FileIperator& f_Begin, const FileIperator& f_End,
      COperatorsArray& f_Result );

}; /* namespace pcl6 */

#endif /* PARSERFUNCTION_HPP_ */
