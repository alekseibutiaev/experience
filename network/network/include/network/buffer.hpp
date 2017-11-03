#pragma once

#ifndef __NETWORK_NETWORK_BUFFER_HPP__
#define __NETWORK_NETWORK_BUFFER_HPP__

#include <vector>
#include <boost/smart_ptr.hpp>

namespace network {

  typedef std::vector< unsigned char > buffer;
  typedef boost::shared_ptr< buffer > buffer_ptr;

}; /* namespace network */

#endif /* __NETWORK_NETWORK_BUFFER_HPP__ */