#pragma once

#ifndef __NETWORK_SESSION_OWNER_FWD_HPP__
#define __NETWORK_SESSION_OWNER_FWD_HPP__

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace network {

  class session_owner;

  struct empty_deliter {
    template < typename TYPE >
    void operator()( TYPE* f_prt ) const {
      std::cout << "empty_deliter: delete TYPE 0x" << f_prt << std::endl;
    }
  };

  typedef boost::shared_ptr< session_owner > session_owner_ptr;
  typedef boost::weak_ptr< session_owner > session_owner_ref;

}; /* namespace network */

#endif /* __NETWORK_SESSION_OWNER_FWD_HPP__ */