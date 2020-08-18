#include <boost/system/error_code.hpp>
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

  inline net::details::io_context_t& get_ctx(resolver_ptr& rsl) {
#if BOOST_VERSION <= 106501
    return rsl->get_io_service();
#else
    return rsl->get_executor().context();
#endif
  }

  void handle_connect(net::details::socket_t* rsocket, net::socket_events_t func,
      const net::error_code_t& err, endpoints_t endpoints) {
    net::details::socket_ptr socket(rsocket);
    func(err ? net::session_ptr() : net::session_t::create(std::move(socket)), err);
  }

  void handle_resolve(resolver_ptr rsl, net::socket_events_t func,
      const net::error_code_t& err, endpoints_t endpoints) {
    if(err)
      func(net::session_ptr(), err);
    else if(net::details::socket_t* socket = new(std::nothrow) net::details::socket_t(get_ctx(rsl)))
      boost::asio::async_connect(*socket, endpoints, std::bind(&handle_connect, socket, func,
        std::placeholders::_1, std::placeholders::_2));
    else
      func(net::session_ptr(), boost::system::error_code(boost::system::errc::not_enough_memory,
        boost::system::generic_category()));
  }

} /* namespace */

namespace net {

  session_ptr connector_t::connect(context_ptr& context, const std::string& host,
      const unsigned short& port, error_code_t& err) {
    return connect(context, host, std::to_string(port), err);
  }

  session_ptr connector_t::connect(context_ptr& context, const std::string& host,
      const std::string& port, error_code_t& err) {
    net::details::io_context_t& ctx = get_ctx(context);
    boost::asio::ip::tcp::resolver rsl(ctx);
    if(details::socket_ptr socket = details::socket_ptr(new(std::nothrow) details::socket_t(ctx))) {
      boost::asio::connect(*socket, rsl.resolve({host, port}), err);
      if(!err)
        return net::session_t::create(std::move(socket));
    }
    else
      err = boost::system::error_code(boost::system::errc::not_enough_memory,
        boost::system::generic_category());
    return session_ptr();
  }

  void connector_t::connect(context_ptr& context, const std::string& host, const unsigned short& port,
      socket_events_t func) {
    connect(context, host, std::to_string(port), func);
  }

  void connector_t::connect(context_ptr& context, const std::string& host, const std::string& port,
      socket_events_t func) {
    resolver_ptr rsl = std::make_shared<boost::asio::ip::tcp::resolver>(get_ctx(context));
    rsl->async_resolve({host, port}, std::bind(&handle_resolve, rsl, func, std::placeholders::_1,
      std::placeholders::_2));
  }

} /* namespace net */
