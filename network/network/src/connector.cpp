#include <boost/asio.hpp>

#include "session.h"
#include "context_details.h"
#include "nettype_details.h"
#include "socket_details.h"

#include "connector.h"

namespace {

  using resolver_ptr = std::shared_ptr<boost::asio::ip::tcp::resolver>;
  using endpoints_t = boost::asio::ip::tcp::resolver::iterator;
  using _socket_ptr = std::shared_ptr<net::details::socket_t>;

  inline net::details::io_context_t& get_ctx(net::context_ptr& value) {
    return static_cast<net::details::context_t&>(*value).get_io_context();
  }

  net::details::io_context_t& get_context(resolver_ptr& rsl) {
#if BOOST_VERSION <= 106501
    return rsl->get_io_service();
#else
    return rsl->get_executor().context();
#endif
  }

  void handle_connect(net::details::socket_t* rsocket, net::accepted_func_t func,
      const net::error_code_t& err, endpoints_t endpoints) {
    net::session_ptr session = err ? net::session_ptr() :
      net::session_t::create(net::details::socket_ptr(rsocket));
    func(session);
  }

  void handle_resolve(resolver_ptr rsl, net::accepted_func_t func, const net::error_code_t& err,
      endpoints_t endpoints) {
    if(!err) {
      net::details::socket_t* socket(new net::details::socket_t(get_context(rsl)));
      boost::asio::async_connect(*socket, endpoints, std::bind(&handle_connect, socket, func,
        std::placeholders::_1, std::placeholders::_2));
      return;
    }
    func(net::session_ptr());
  }

} /* namespace */

namespace net {

  session_ptr connector_t::connect(context_ptr& context, const std::string& host, const unsigned short& port) {
    return connect(context, host, std::to_string(port));
  }

  session_ptr connector_t::connect(context_ptr& context, const std::string& host, const std::string& port) {
    try {
      boost::asio::ip::tcp::resolver rsl(get_ctx(context));
      details::socket_ptr socket(new details::socket_t(get_ctx(context)));
      boost::asio::connect(*socket, rsl.resolve({host, port}));
      session_ptr res = net::session_t::create(std::move(socket));
      return res;
    }
    catch(const boost::system::system_error&) {
    }
    catch(const std::exception&) {
    }
    return session_ptr();
  }

  void connector_t::connect(context_ptr& context, const std::string& host, const unsigned short& port, accepted_func_t func) {
    connect(context, host, std::to_string(port), func);
  }

  void connector_t::connect(context_ptr& context, const std::string& host, const std::string& port, accepted_func_t func) {
    resolver_ptr rsl = std::make_shared<boost::asio::ip::tcp::resolver>(get_ctx(context));
    rsl->async_resolve({host, port}, std::bind(&handle_resolve, rsl, func, std::placeholders::_1,
      std::placeholders::_2));
  }

} /* namespace net */
