//*****************************************************************************
//        File: StaticIf.hpp
//     Project: kopirkin
//  Created on: 02.12.2009
//      Author: alexsy
//        Name: Butyaev A.J.
//      e-mail: alexsyrezerv@mail.ru
//*****************************************************************************

#ifndef __STATICIF_HPP__
#define __STATICIF_HPP__

namespace pcl6 {

  template< bool CONDITION, typename THEN, typename ELSE >
  struct if_c {
      typedef THEN type;
  };

  template< typename THEN, typename ELSE >
  struct if_c< false, THEN, ELSE > {
      typedef ELSE type;
  };

}; /* namespace pcl6 */

#endif /* __STATICIF_HPP__ */
