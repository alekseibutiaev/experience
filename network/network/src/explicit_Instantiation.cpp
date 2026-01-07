#include "boost/asio.hpp"

#include "nettype_details.h"
#include "session_details.h"
#include "acceptor_details.h"

template class net::details::session_t<net::details::tcp_ip_protocol_t>;
template class net::details::session_t<net::details::local_stream_protocol_t>;
template class net::details::acceptor_t<net::details::tcp_ip_protocol_t>;
template class net::details::acceptor_t<net::details::local_stream_protocol_t>;
