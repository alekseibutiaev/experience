
#include "session.h"
#include "context_details.h"
#include "nettype_details.h"
#include "session_details.h"
#include "acceptor_details.h"

namespace net {

  acceptor_ptr acceptor_t::tcp_ip_v4(context_ptr& context, const unsigned short& port) {
    auto ac = details::tcp_ip_protocol_t::acceptor(
      static_cast<details::context_t&>(*context).get_io_context(),
      details::tcp_ip_protocol_t::endpoint(details::tcp_ip_protocol_t::v4(), port));
    return acceptor_ptr(new net::details::acceptor_t<details::tcp_ip_protocol_t>(context, std::move(ac)));
  }

  acceptor_ptr acceptor_t::local_stream_protocol(context_ptr& context, const std::string& file) {
    auto ac = details::local_stream_protocol_t::acceptor(
      static_cast<details::context_t&>(*context).get_io_context(),
      details::local_stream_protocol_t::endpoint(file));
    return acceptor_ptr(new net::details::acceptor_t<details::local_stream_protocol_t>(context, std::move(ac)));
  }

} /* namespace net */
