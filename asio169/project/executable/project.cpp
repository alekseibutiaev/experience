#if 1
#include <iostream>
#include <functional>
#include <stdexcept>
#include <string_view>
#include <memory>
#include <thread>

#include <boost/asio.hpp>

const std::string_view host = "www.google.com";
const std::string_view service = "80";

bool stop = false;


void resolve_handle(const boost::system::error_code e, boost::asio::ip::tcp::resolver::results_type res) {
  if(e) {
    std::cout << e.message() << std::endl;
    return;
  }
  std::cout << res.size() << std::endl;
      stop = true;
}

struct th_t {
  th_t(boost::asio::io_context& ctx) : m_ctx(ctx) {}
  void run() {
    m_ctx.run();
  }
  boost::asio::io_context& m_ctx;
};

int main(int ac, char* av[]) {
  try {
    boost::asio::io_context ioctx;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> wg(boost::asio::make_work_guard(ioctx));
    th_t ttt(ioctx);

    auto th = std::thread(&th_t::run, std::ref(ttt));

    boost::asio::ip::tcp::resolver res(ioctx);
    //res.async_resolve(host, service, std::bind(&resolve_handle, std::placeholders::_1, std::placeholders::_2));
    auto r = res.resolve(host, service);
    boost::asio::ip::tcp::socket s(ioctx);
    boost::asio::connect(s, r.begin(), r.end());
    while(!stop)
        std::this_thread::sleep_for(std::chrono::seconds(1));

    if(th.joinable()) {
      ioctx.stop();
      th.join();
    }

    return 0;
  }
  catch(const std::exception& e){
    std::cerr << e.what() << std::endl;
  } 
  catch(...) {
    std::cerr << "unknown" << std::endl;
  }
  return 1;
}
#else
#include <string>
#include <iostream>
#include <thread>

// The function we want to execute on the new thread.
void task1(std::string msg) {
  for(std::size_t i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << i << " " << msg  << std::endl;
  }
}

int main() {
    // Constructs the new thread and runs it. Does not block execution.
    std::thread t1(task1, "Hello");

    // Do other things...
    std::this_thread::sleep_for(std::chrono::seconds(10));
    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    if(t1.joinable())
      t1.join();
}
#endif
