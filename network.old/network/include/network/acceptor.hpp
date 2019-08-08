#pragma once

#ifndef __NETWORK_ACCEPTOR_HPP__
#define __NETWORK_ACCEPTOR_HPP__

#include <string>

#include "handler.hpp"
#include "network_export.hpp"

namespace network {

  class acceptor_impl;
  class session_owner_delegate;

  class NETWORK_SYMBOL acceptor {
  public:
    acceptor( const unsigned short& f_port, creator_ptr& f_creator );
    acceptor( const std::string& f_address, const unsigned short& f_port, creator_ptr& f_creator );
    ~acceptor();
  private:
    acceptor_impl* pv_impl;
  };

}; /* namespace network */

#endif /* __NETWORK_ACCEPTOR_HPP__ */
