#pragma once

#ifndef __NETWORK_HANDLER_HPP__
#define __NETWORK_HANDLER_HPP__

#include <boost/shared_ptr.hpp>

#include "buffer.hpp"
#include "network_export.hpp"

namespace network {

  class NETWORK_SYMBOL session_transmiter {
  public:
    virtual void transmit( const buffer_ptr& f_data ) = 0;
    virtual void close() = 0;
  protected:
    virtual ~session_transmiter();
  };

  class NETWORK_SYMBOL session_receiver {
  public:
    virtual ~session_receiver();
    virtual void connected( session_transmiter* f_transmiter ) = 0;
    virtual void disconnected() = 0;
    virtual void closed() = 0;
    virtual void receive( const buffer_ptr& f_data ) = 0;
  };

  typedef boost::shared_ptr< session_receiver > session_receiver_ptr; 

  class NETWORK_SYMBOL creator {
  public:
    virtual ~creator();
    virtual session_receiver_ptr create() = 0;
  };

  typedef boost::shared_ptr< creator > creator_ptr;

}; /* namespace network */

#endif /* __NETWORK_HANDLER_HPP__ */