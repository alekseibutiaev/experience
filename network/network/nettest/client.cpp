#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <functional>

#include "network.h"
#include "clparametrs.h"

namespace {

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
    void write(const std::string& msg) {
      net::buffer_ptr buf = std::make_shared<net::buffer_t>(msg.begin(), msg.end());
      m_session->send(buf);
    }
  private:
    void receive(const net::buffer_ptr buf) {
      std::cout << "replay: " << std::string(buf->begin(), buf->end()) << std::endl;
    }
  private:
    net::session_ptr m_session;
  };

  using echo_ptr = std::shared_ptr<echo_t>;

  echo_ptr echo;
  bool cn = false;
  std::mutex mtx;
  std::condition_variable cv;

  void connected(net::session_ptr sess, const net::error_code_t& err) {
    if(err)
      std::cerr << err.message() << std::endl;
    else
      echo = std::make_shared<echo_t>(sess);
    std::lock_guard<std::mutex> _(mtx);
    cn = true;
    cv.notify_one();
  }

  void error_handle(const net::error_code_t&){
  }

} /* namespace */

int main(int ac, char* av[]) {
  std::cout << BOOST_VERSION << std::endl;
  try {
    if(const auto& opt = cl::get_options(ac, av)) {

      net::context_ptr ctx = net::context_t::create(std::bind(error_handle, std::placeholders::_1));
      std::thread th([&ctx](){
        ctx->run();
        std::cout << "stop thread" << std::endl;
      });
      net::connector_t::tcp_ip_v4(ctx, opt->host, opt->port, std::bind(&connected,
        std::placeholders::_1, std::placeholders::_2));
      std::unique_lock<std::mutex> _(mtx);
      while(!cn)
        cv.wait(_);
      if(echo) {
        echo->start();
        std::string msg;
        for(;;) {
          std::cin >> msg;
          if("quit" == msg)
            break;
          echo->write(msg);
        }
      }
      if(th.joinable()) {
        ctx->stop();
        th.join();
      }
    }
  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}