#include <iostream>
#include <string>
#include <stdexcept>
#include <list>
#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>

#include <boost/asio.hpp>

template< typename type_t >
class cache_queue {
public:

	typedef type_t value_t;
	typedef std::list<type_t> queue_t; 

public:

	void add( const type_t& value ) {
		if( !cache_node.empty() ) {
			queue.splice(queue.end(), cache_node, cache_node.begin() );
			queue.back() = std::move(value);
		}
		else
			queue.emplace_back( value );
	}

	type_t& front() {
		return queue.front();
	}

	void store_front() {
		cache_node.splice(cache_node.end(), queue, queue.begin() );
	}

	bool empty() const {
		return queue.empty();
	}

	queue_t& data() {
		return queue;
	}

	void store_data( queue_t& value ) {
		cache_node.splice(cache_node.end(), value);
	}

private:

	queue_t queue;
	queue_t cache_node;

};

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
			std::cerr << "log stop" << std::endl;
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

std::unique_ptr<logger> logger::mylog;


void task( int strand_id, std::thread::id id )
{
	logger::out( "strand_id: ", strand_id ," invoke from: ", id,
		" current thread: ", std::this_thread::get_id(), '\n' );
}  

const size_t maxstrand = 5;

int main( int ac, char* av[] ) {
	logger::out( STRING_DEFENITION, '\n' );
	try {

		boost::asio::io_service ios;
		std::vector< std::shared_ptr< boost::asio::io_service::strand > > strands;
		for( size_t i = 0; i < maxstrand; ++i )
			strands.emplace_back( std::make_shared< boost::asio::io_service::strand >( ios ) );
		std::thread iost( [&ios](){ ios.run(); } );
		for( size_t i = 0; i < maxstrand; ++i ) {
			for( size_t j = 0; j < 500; ++j )
					strands[ i ]->post( std::bind( task, i, std::this_thread::get_id() ) );
		}
		logger::out( "reset strand", '\n' );
		strands[0].reset();
		//ios.stop();
		iost.join();
	}
	catch( const std::exception& e ) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
