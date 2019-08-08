#include "stdafx.h"

#include "connector_impl.hpp"

#include <network/connector.hpp>

namespace network {

  connector::connector() : pv_impl( new connector_impl() ) {
    pv_impl->use_face( this );
  }

  connector::~connector() {
    delete pv_impl;
  }

  void connector::connect( const std::string& f_address, const unsigned short& f_port, creator* f_creator ) {
    pv_impl->connect( f_address, f_port, f_creator );
  }

}; /* namespace network */
