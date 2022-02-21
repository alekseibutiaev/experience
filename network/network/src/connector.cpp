#include <boost/asio.hpp>

#include "session.h"
#include "context_details.h"
#include "nettype_details.h"
#include "session_details.h"

#include "connector.h"

namespace {

  using resolver_ptr = std::shared_ptr<net::details::tcp_ip_protocol_t::resolver>;
  using endpoints_t = net::details::tcp_ip_protocol_t::resolver::iterator;
  using socket_t = net::details::session_t<net::details::tcp_ip_protocol_t>::socket_type;
  using socket_ptr = std::shared_ptr<socket_t>;

  inline net::details::io_context_t& get_ctx(net::context_ptr& value) {
    return static_cast<net::details::context_t&>(*value).get_io_context();
  }

  void handle_connect(socket_ptr socket, net::socket_events_t func,
      const net::error_code_t& err, endpoints_t endpoints) {
    net::session_ptr session = err ? net::session_ptr() :
      std::make_shared<net::details::session_t<net::details::tcp_ip_protocol_t>>(std::move(*socket));
    func(session, err);
  }

  void handle_resolve(resolver_ptr, net::context_ptr& context, net::socket_events_t func,
      const net::error_code_t& err, endpoints_t endpoints) {
    if(!err) {
      auto socket = std::make_shared<socket_t>(get_ctx(context));
      boost::asio::async_connect(*socket, endpoints, std::bind(&handle_connect, socket, func,
        std::placeholders::_1, std::placeholders::_2));
      return;
    }
    func(net::session_ptr(), err);
  }

} /* namespace */

namespace net {

  session_ptr connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const unsigned short& port) {
    return tcp_ip_v4(context, host, std::to_string(port));
  }

  session_ptr connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const std::string& port) {
    auto& ctx = get_ctx(context);
    socket_t socket(ctx);
    error_code_t err;
    boost::asio::connect(socket, net::details::tcp_ip_protocol_t::resolver(ctx).resolve({host, port}), err);
    return err ? net::session_ptr() :
      std::make_shared<net::details::session_t<net::details::tcp_ip_protocol_t>>(std::move(socket));
  }

  void connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const unsigned short& port,
      socket_events_t func) {
    tcp_ip_v4(context, host, std::to_string(port), func);
  }

  void connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const std::string& port,
      socket_events_t func) {
    auto rsl = std::make_shared<net::details::tcp_ip_protocol_t::resolver>(get_ctx(context));
    rsl->async_resolve({host, port}, std::bind(&handle_resolve, rsl, std::ref(context), func,
      std::placeholders::_1, std::placeholders::_2));
  }

} /* namespace net */
