//*****************************************************************************
//        File: Common.hpp
//     Project: kopirkin
//  Created on: 04.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <iterator>

namespace pcl6 {

  typedef unsigned char Byte;
  typedef std::istreambuf_iterator< char, std::char_traits< char > > FileIperator;

}; /* namespace pcl6 */

#endif /* __COMMON_HPP__ */
