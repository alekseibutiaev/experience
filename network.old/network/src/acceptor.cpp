#include "stdafx.h"

#include "acceptor_impl.hpp"

#include <network/acceptor.hpp>

namespace network {

  acceptor::acceptor( const unsigned short& f_port, creator_ptr& f_creator ) :
    pv_impl( new acceptor_impl( f_port, f_creator ) ) {
  }

  acceptor::acceptor( const std::string& f_address, const unsigned short& f_port, creator_ptr& f_creator ) :
    pv_impl( new acceptor_impl( f_address, f_port, f_creator ) ) {
  }

  acceptor::~acceptor() {
    delete pv_impl;
  }

}; /* namespace network */
