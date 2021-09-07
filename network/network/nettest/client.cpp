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
  std::mutex mtx;
  std::condition_variable cv;

  void connected(net::session_ptr sess) {
    std::lock_guard<std::mutex> _(mtx);
    echo = std::make_shared<echo_t>(sess);
    cv.notify_one();
  }

  void error_handle(bool, const char*, const int, const net::error_code_t&){
  }

} /* namespace */

int main(int ac, char* av[]) {
  try {
    if(const auto& opt = cl::get_options(ac, av)) {
      net::context_ptr ctx = net::context_t::create(std::bind(error_handle, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
      std::thread th([&ctx](){
        ctx->run();
        std::cout << "stop thread" << std::endl;
      });
      net::connector_t::connect(ctx, opt->host, opt->port, std::bind(&connected, std::placeholders::_1));
      std::unique_lock<std::mutex> _(mtx);
      while(!echo)
        cv.wait(_);
      echo->start();
      std::string msg;
      for(;;) {
        std::cin >> msg;
        if("quit" == msg)
          break;
        echo->write(msg);
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