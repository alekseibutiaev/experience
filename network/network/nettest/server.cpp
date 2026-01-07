#include <map>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <functional>

#include "network.h"
#include "clparametrs.h"

namespace  {

  class echo_t {
  public:
    echo_t(net::session_ptr session, const bool& no_echo)
        : m_session(session)
        , m_no_echo(no_echo) {
      m_session->receive_callback(std::bind(&echo_t::receive, this, std::placeholders::_1));
    }
    ~echo_t() {
      m_session->close();
    }
    void start() {
      m_session->read();
    }
  private:
    void receive(const net::buffer_ptr buf) {
      std::cout << std::string(buf->begin(), buf->end()) << std::endl;
      if(!m_no_echo)
        m_session->send(buf);
    }
  private:
    net::session_ptr m_session;
    const bool& m_no_echo;
  };

  using echo_ptr = std::shared_ptr<echo_t>;

  class echo_server_t {
  public:
    echo_server_t(net::context_ptr& ctx, const cl::params_t& param)
        : m_ctx(ctx)
        , m_param(param)
        , m_acceptor(get_acceptor(m_ctx, m_param)){
      m_acceptor->accepted_callback(std::bind(&echo_server_t::accepted, this, std::placeholders::_1));
      m_acceptor->error_callback(std::bind(&echo_server_t::empty_error, this, std::placeholders::_1));
      m_acceptor->listen();
    }
  private:
    using echo_map_t = std::map<net::session_ptr, echo_ptr>;
  private:
    void accepted(net::session_ptr session) {
      session->disconnect_callback(std::bind(&echo_server_t::disconnected, this,
        std::placeholders::_1, std::placeholders::_2));
      echo_ptr echo(new echo_t(session, m_param.no_echo));
      m_echo_map[session] = echo;
      echo->start();
    }
    void disconnected(net::session_ptr session, const net::error_code_t& err) {
      std::cout << "disconnected " << err.message() << std::endl;
      m_echo_map.erase(session);
    }
    net::acceptor_ptr get_acceptor(net::context_ptr& ctx, const cl::params_t& param) {
      return param.file.empty() ? net::acceptor_t::tcp_ip_v4(m_ctx, param.port) :
        net::acceptor_t::local_stream_protocol(m_ctx, param.file);
    }
    void empty_error(const net::error_code_t& err) {
      std::cout << "Error: " << err.message() << std::endl;
    }
  private:
    net::context_ptr& m_ctx;
    const cl::params_t& m_param;
    net::acceptor_ptr m_acceptor;
    echo_map_t m_echo_map;
  };

  void error_handle(const net::error_code_t&) {
  }

} /* namespace */

int main(int ac, char* av[]) {

  try {
    if(const auto& opt = cl::get_options(ac, av)) {
      net::context_ptr ctx = net::context_t::create(std::bind(error_handle, std::placeholders::_1));
      echo_server_t se(ctx, *opt);
      ctx->run();
    }
  }
  catch(const std::exception& e) {
  }
  return 0;
}