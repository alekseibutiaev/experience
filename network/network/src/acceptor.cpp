#include "acceptor_details.h"

#include "acceptor.h"


namespace net {

  acceptor_ptr acceptor_t::create(context_ptr& context, unsigned short port) {
    return acceptor_ptr(new net::details::acceptor_t(context, port));
  }

} /* namespace net */
