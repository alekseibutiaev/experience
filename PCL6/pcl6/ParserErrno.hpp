//*****************************************************************************
//        File: ParserErrno.hpp
//     Project: kopirkin
//  Created on: 06.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __PARSERERRNO_HPP__
#define __PARSERERRNO_HPP__

namespace pcl6 {

  namespace PCLErr {
    enum Number{
      NoError               = 0,
      OpenError             = 1,
      UnknownFormat         = 2,
      UnknownTag            = 3,
      UnexpectedEnd         = 4,
      NotDisassembled       = 5,
      UncorrectPageCount    = 6,
      InvalidAttrID         = 7,
      InvalidData           = 8,
      InvalidAttrSet        = 9,
      InvalidStrOpr         = 10,
      InvalidEmbData        = 11,
      ReadArrayData         = 12,
      AllocateArray         = 13,
      AllocateObject        = 14,
      Max
    };
  };

  extern int PCLErrno;
  // Get error string
  const char* ErrorString();

} /* namespace pcl6 */

#endif /* __PARSERERRNO_HPP__ */
