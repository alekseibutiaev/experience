//*****************************************************************************
//        File: ParserErrno.cpp
//     Project: kopirkin
//  Created on: 06.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#include <cstdlib>
#include "ParserErrno.hpp"

namespace pcl6 {


  const std::size_t MaxBuf = 300;

//  const char* const UnknownTag = "Unknown pcl6 tag: 0x%02X";

  char errorbuf[ MaxBuf ];

  const char* cErrorMessage[] = {
    "",
    "The file is not opened.",
    "Unknown format of a file.",
    "Unknown PCL6 tag.",
    "The unexpected end of a file.",
    "File not disassembled.",
    "It is not probably correct to count up pages.",
    "Not the correct identifier of attribute",
    "Not a correct block of the data.",
    "The set of attributes is not correct.",
    "The string operator is not correct."
    "The embed data is not correct.",
    "Can not read of data array.",
    "Can not allocated of data array."
    "Can not allocated of object."
  };
//*****************************************************************************
  int PCLErrno;
//*****************************************************************************
  const char* ErrorString( const PCLErr::Number& f_ErrNo ){
    if( f_ErrNo < PCLErr::Max )
      return cErrorMessage[ f_ErrNo ];
    return "";
  }


} /* namespace pcl6 */

