#include <boost/asio.hpp>

#include "session.h"
#include "context_details.h"
#include "nettype_details.h"
#include "session_details.h"

#include "connector.h"

namespace {

  using resolver_ptr = std::shared_ptr<net::details::tcp_ip_protocol_t::resolver>;
#if BOOST_VERSION < 106600
  using results_t = net::details::tcp_ip_protocol_t::resolver::iterator;
  using iterator_t = results_t;
#else
  using results_t = net::details::tcp_ip_protocol_t::resolver::results_type;
  using iterator_t = results_t::iterator;
#endif
  using socket_t = net::details::session_t<net::details::tcp_ip_protocol_t>::socket_type;
  using socket_ptr = std::shared_ptr<socket_t>;

#if BOOST_VERSION < 106600
  iterator_t begin(results_t& value) {
    return value;
  }
  iterator_t end(results_t& value) {
    return iterator_t();
  }
#else
  iterator_t begin(results_t& value) {
    return value.begin();
  }
  iterator_t end(results_t& value) {
    return value.end();
  }
#endif


  inline net::details::io_context_t& get_ctx(net::context_ptr& value) {
    return static_cast<net::details::context_t&>(*value).get_io_context();
  }

  void handle_connect(socket_ptr socket, net::socket_events_t func,
      const net::error_code_t& err, iterator_t) {
    net::session_ptr session = err ? net::session_ptr() :
      std::make_shared<net::details::session_t<net::details::tcp_ip_protocol_t>>(std::move(*socket));
    func(session, err);
  }

  void handle_resolve(resolver_ptr, net::context_ptr& context, net::socket_events_t func,
      const net::error_code_t& err, results_t results) {
    if(!err) {
      auto socket = std::make_shared<socket_t>(get_ctx(context));
      boost::asio::async_connect(*socket, begin(results), end(results), std::bind(&handle_connect, socket, func,
        std::placeholders::_1, std::placeholders::_2));
      return;
    }
    func(net::session_ptr(), err);
  }

} /* namespace */

namespace net {

  session_ptr connector_t::tcp_ip_v4(context_ptr& context, const std::string& host,
      const unsigned short& port, error_code_t& err) {
    return tcp_ip_v4(context, host, std::to_string(port), err);
  }

#if BOOST_VERSION < 106600
  session_ptr connector_t::tcp_ip_v4(context_ptr& context, const std::string& host,
      const std::string& port, error_code_t& err) {
    auto& ctx = get_ctx(context);
    auto results = net::details::tcp_ip_protocol_t::resolver(ctx).resolve({host, port}, err);
    if(err)
      return net::session_ptr();
    socket_t socket(ctx);
    boost::asio::connect(socket, begin(results), end(results), err);
    return err ? net::session_ptr() :
      std::make_shared<net::details::session_t<net::details::tcp_ip_protocol_t>>(std::move(socket));
  }
#else
  session_ptr connector_t::tcp_ip_v4(context_ptr& context, const std::string& host,
      const std::string& port, error_code_t& err) {
    auto& ctx = get_ctx(context);
    auto results = net::details::tcp_ip_protocol_t::resolver(ctx).resolve(host, port, err);
    if(err)
      return net::session_ptr();
    socket_t socket(ctx);
    boost::asio::connect(socket, results.begin(), results.end(), err);
    return err ? net::session_ptr() :
      std::make_shared<net::details::session_t<net::details::tcp_ip_protocol_t>>(std::move(socket));
  }
#endif

  void connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const unsigned short& port,
      socket_events_t func) {
    tcp_ip_v4(context, host, std::to_string(port), func);
  }

#if BOOST_VERSION < 106600
  void connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const std::string& port,
      socket_events_t func) {
    auto rsl = std::make_shared<net::details::tcp_ip_protocol_t::resolver>(get_ctx(context));
    rsl->async_resolve({host, port}, std::bind(&handle_resolve, rsl, std::ref(context), func,
      std::placeholders::_1, std::placeholders::_2));
  }
#else
  void connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const std::string& port,
      socket_events_t func) {
    auto rsl = std::make_shared<net::details::tcp_ip_protocol_t::resolver>(get_ctx(context));
    rsl->async_resolve(host, port, std::bind(&handle_resolve, rsl, std::ref(context), func,
      std::placeholders::_1, std::placeholders::_2));
  }
#endif

} /* namespace net */
