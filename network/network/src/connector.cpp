#include <type_traits>
#include <initializer_list>
#include <boost/asio.hpp>

#include "session.h"
#include "context_details.h"
#include "nettype_details.h"
#include "session_details.h"

#include "connector.h"

namespace {

  inline net::details::io_context_t& get_ctx(net::context_ptr& value) {
    return static_cast<net::details::context_t&>(*value).get_io_context();
  }

} /* namespace */

namespace net {

  namespace details {

    template<typename protocol_t>
    class connector_t {
    public:
      using protocol_type = protocol_t;
      using socket_t = typename net::details::session_t<protocol_type>::socket_type;
      using socket_ptr = typename std::shared_ptr<socket_t>;
      using endpoint_type = typename protocol_type::endpoint;

      enum { tcp_ip = std::is_same<protocol_type, tcp_ip_protocol_t>::value };

      using resolver_type = typename std::enable_if<tcp_ip, typename protocol_type::resolver>::type;

      using query_type = typename std::enable_if<tcp_ip, typename resolver_type::query>::type;

      using resolver_ptr = typename std::enable_if<tcp_ip, typename std::shared_ptr<resolver_type>>::type;

      using endpoints_type = typename std::conditional<tcp_ip,
        typename protocol_type::resolver::iterator,
        std::initializer_list<std::string>::iterator>::type;

    public:
      static session_ptr connect(context_ptr& context, const query_type& query) {
        auto& ctx = get_ctx(context);
        socket_t socket(ctx);
        error_code_t err;
        boost::asio::connect(socket, resolver_type(ctx).resolve(query, err));
        return err ? session_ptr() : std::make_shared<net::details::session_t<protocol_type>>(std::move(socket));
      }
      static void connect(context_ptr& context, socket_events_t func, const query_type& query) {
        auto& ctx = get_ctx(context);
        auto rsl = std::make_shared<resolver_type>(ctx);
        rsl->async_resolve(query, std::bind(connector_t::handle_resolve, rsl, std::ref(ctx), func,
          std::placeholders::_1, std::placeholders::_2));
      }
/*
      static void connect(context_ptr& context, socket_events_t func, const std::string& query) {
        auto& ctx = get_ctx(context);
      }
*/
    private:
      static void handle_resolve(resolver_ptr, net::details::io_context_t& ctx, socket_events_t func,
          const error_code_t& err, endpoints_type endpoints) {
        if(!err) {
          auto socket = std::make_shared<socket_t>(ctx);
          boost::asio::async_connect(*socket, endpoints, std::bind(connector_t::handle_connect, socket, func,
            std::placeholders::_1, std::placeholders::_2));
          return;
        }
        func(net::session_ptr(), err);
      }
      static void handle_connect(socket_ptr socket, socket_events_t func, const error_code_t& err, endpoints_t endpoints) {
        session_ptr session = err ? session_ptr() :
          std::make_shared<net::details::session_t<protocol_type>>(std::move(*socket));
        func(session, err);
      }
    };

  } /* namespace details */

  session_ptr connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const unsigned short& port) {
    return tcp_ip_v4(context, host, std::to_string(port));
  }

  session_ptr connector_t::tcp_ip_v4(context_ptr& context, const std::string& host, const std::string& port) {
    return details::connector_t<details::tcp_ip_protocol_t>::connect(context, {host, port});
  }

  void connector_t::tcp_ip_v4(context_ptr& context, socket_events_t func, const std::string& host, const unsigned short& port) {
    tcp_ip_v4(context, func, host, std::to_string(port));
  }

  void connector_t::tcp_ip_v4(context_ptr& context, socket_events_t func, const std::string& host, const std::string& port) {
    details::connector_t<details::tcp_ip_protocol_t>::connect(context, func, {host, port});
  }

  session_ptr connector_t::local_stream(context_ptr& context, const std::string& file) {
    //return details::connector_t<details::local_stream_protocol_t>::connect(context, file);
  }

  void connector_t::local_stream(context_ptr& context, socket_events_t func, const std::string& file) {
    //details::connector_t<details::local_stream_protocol_t>::connect(context, func, file);
  }

} /* namespace net */
