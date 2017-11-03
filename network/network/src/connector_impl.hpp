#pragma once

#ifndef __NETWORK_CONNECTOR_IMPL_HPP__
#define __NETWORK_CONNECTOR_IMPL_HPP__

#include <string> 

#include "session_owner.hpp"

namespace network {

  class creator;
  class connector;

  class connector_impl {
  public:
    connector_impl();
    ~connector_impl();
    void use_face( connector* f_face );
    void connect( const std::string& f_address, const unsigned short& f_port, creator* f_creator );
  private:
    void pv_connect_handler( session_owner_ptr f_awaiting, const boost::system::error_code& error );
  private:
     connector* pv_face; 

  };

}; /* namespace network */

#endif /* __NETWORK_CONNECTOR_IMPL_HPP__ */
