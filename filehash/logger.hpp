#include <list>
#include <mutex>
#include <thread>
#include <memory>
#include <sstream>
#include <iterator>
#include <iostream>
#include <condition_variable>

#include "cache_queue.hpp"

namespace tools {

  class logger {

  public:

	  logger() try : _stop(false), th( [&](){ out_tread(); } ) {
	  }
	  catch (const std::exception& e) {
		  std::cerr << "error: " << e.what() << std::endl;
		  stop();
		  throw(std::runtime_error("log exception."));
	  }
	  catch (...) {
		  std::cerr << "unknown mistake" << std::endl;
		  stop();
		  throw(std::runtime_error("log exception."));
	  }

	  ~logger() {
		  stop();
	  }

	  void stop() {
		  if (th.joinable()) {
			  {
				  std::unique_lock<std::mutex> _(mtx);
				  _stop = true;
				  cv.notify_one();
			  }
			  th.join();
		  }
	  }

	  static void out(std::stringstream& stream) {
		  if (!mylog)
			  mylog.reset( new logger() );
		  mylog->out_int( stream.str() );
	  }

	  template <typename type1_t, typename... types_t >
	  static void out(std::stringstream& stream, const type1_t& value, const types_t&... values) {
		  stream << value;
		  out(stream, values...);
	  }

	  template <typename type1_t, typename... types_t >
	  static void out(const type1_t& value, const types_t&... values) {
		  std::stringstream stream;
		  stream << value;
		  out(stream, values...);
	  }

  public:

	  static const char endl;

  private:

	  struct string_wrapper {
		  explicit string_wrapper( const std::string& _value ) : value(_value){}
		  const std::string& value;
	  };

	  typedef cache_queue<std::string> storage_t;

  private:

	  void out_int( const std::string& value ) {
		  std::unique_lock<std::mutex> _(mtx);
		  queue.add(value);
		  cv.notify_one();
	  }

	  void out_tread() {
		  try {
			  storage_t::queue_t local;
			  while ( !_stop || !queue.empty() ) {
				  {
					  std::unique_lock<std::mutex> _(mtx);
					  while (!_stop && queue.empty())
						  cv.wait(_);
					  local.swap(queue.data());
				  }
				  std::copy(local.begin(), local.end(), std::ostream_iterator<std::string>(std::cout));
				  std::unique_lock<std::mutex> _(mtx);
				  queue.store_data( local );
			  }
		  }
		  catch (const std::exception& e) {
			  std::cerr << e.what() << std::endl;
		  }
	  }

  private:

	  bool _stop;
	  storage_t queue;
	  std::mutex mtx;
	  std::condition_variable cv;
	  std::thread th;

  private:
	  static std::unique_ptr<logger> mylog;
  };

  const char logger::endl = '\n';
  std::unique_ptr<logger> logger::mylog;

} /* namespace tools */

template <typename type1_t, typename... types_t >
void logout(const type1_t& value, const types_t&... values) {
  tools::logger::out(value, values...);
}

