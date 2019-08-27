#include <map>
#include <memory>
#include <functional>
#include <stdexcept>

#include "network.h"

namespace  {

  class echo_t {
  public:
    echo_t(net::session_ptr session)
        : m_session(session) {
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
      m_session->send(buf);
    }
  private:
    net::session_ptr m_session;
  };

  using echo_ptr = std::shared_ptr<echo_t>;

  class echo_server_t {
  public:
    echo_server_t(net::context_ptr& ctx)
        : m_ctx(ctx)
        , m_acceptor(net::acceptor_t::create(m_ctx, 55555)) {
      m_acceptor->accepted_callback(std::bind(&echo_server_t::accepted, this,
        std::placeholders::_1));
      m_acceptor->listen();
    }
  private:
    using echo_map_t = std::map<net::session_ptr, echo_ptr>;
  private:
    void accepted(net::session_ptr session) {
      session->disconnect_callback(std::bind(&echo_server_t::disconnected, this,
        std::placeholders::_1, std::placeholders::_2));
      echo_ptr echo(new echo_t(session));
      echo->start();
      m_echo_map[session] = echo;
    }
    void disconnected(net::session_ptr session, const net::error_code_t& err) {
      m_echo_map.erase(session);
    }
  private:
    net::context_ptr& m_ctx;
    net::acceptor_ptr m_acceptor;
    echo_map_t m_echo_map;
  };

} /* namespace */

int main(int ac, char* av[]) {

  try {
    net::context_ptr ctx = net::context_t::create();
    echo_server_t se(ctx);
    ctx->run();
  }
  catch(const std::exception& e) {
  }
  return 0;
}