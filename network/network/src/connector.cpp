#include <boost/asio.hpp>

#include "session.h"
#include "context_details.h"
#include "nettype_details.h"
#include "socket_details.h"

#include "connector.h"

namespace {

  using resolver_ptr = std::shared_ptr<boost::asio::ip::tcp::resolver>;
  using endpoints_t = boost::asio::ip::tcp::resolver::iterator;

  inline net::details::io_context_t& get_ctx(net::context_ptr& value) {
    return static_cast<net::details::context_t&>(*value).get_io_context();
  }

  void handle_connect(net::details::socket_t* rsocket, net::socket_events_t func,
      const net::error_code_t& err, endpoints_t endpoints) {
    net::details::socket_ptr socket(rsocket);
    net::session_ptr session = err ? net::session_ptr() : net::session_t::create(std::move(socket));
    func(session, err);
  }

  void handle_resolve(resolver_ptr, net::context_ptr& context, net::socket_events_t func,
      const net::error_code_t& err, endpoints_t endpoints) {
    if(!err) {
      net::details::socket_t* socket = new net::details::socket_t(get_ctx(context));
      boost::asio::async_connect(*socket, endpoints, std::bind(&handle_connect, socket, func,
        std::placeholders::_1, std::placeholders::_2));
      return;
    }
    func(net::session_ptr(), err);
  }

} /* namespace */

namespace net {

  session_ptr connector_t::connect(context_ptr& context, const std::string& host, const unsigned short& port) {
    return connect(context, host, std::to_string(port));
  }

  session_ptr connector_t::connect(context_ptr& context, const std::string& host, const std::string& port) {
    net::details::io_context_t& ctx = get_ctx(context);
    boost::asio::ip::tcp::resolver rsl(ctx);
    if(details::socket_ptr socket = details::socket_ptr(new(std::nothrow) details::socket_t(ctx))) {
      boost::system::error_code err;
      boost::asio::connect(*socket, rsl.resolve({host, port}), err);
      if(!err)
        return net::session_t::create(std::move(socket));
    }
    return session_ptr();
  }

  void connector_t::connect(context_ptr& context, const std::string& host, const unsigned short& port,
      socket_events_t func) {
    connect(context, host, std::to_string(port), func);
  }

  void connector_t::connect(context_ptr& context, const std::string& host, const std::string& port,
      socket_events_t func) {
    resolver_ptr rsl = std::make_shared<boost::asio::ip::tcp::resolver>(get_ctx(context));
    rsl->async_resolve({host, port}, std::bind(&handle_resolve, rsl, std::ref(context), func,
      std::placeholders::_1, std::placeholders::_2));
  }

} /* namespace net */
