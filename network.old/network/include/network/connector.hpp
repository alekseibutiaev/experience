#pragma once

#ifndef __NETWORK_CONNECTOR_HPP__
#define __NETWORK_CONNECTOR_HPP__

#include <string>

//#include "handler.hpp"

#include "network_export.hpp"

namespace network {

  class creator;
  class connector_impl;

  class NETWORK_SYMBOL connector {
  public:
    connector();
    ~connector();
    void connect( const std::string& f_address, const unsigned short& f_port, creator* f_creator );
  private:
    connector_impl* pv_impl;
  };

}; /* namespace network */

#endif /* __NETWORK_CONNECTOR_HPP__ */
