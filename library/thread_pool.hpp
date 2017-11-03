#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>

#include "logger.hpp"
 
template< unsigned int N >
class thread_pool {
public:

	typedef std::function<void()> function_t;

public:

	thread_pool() try : _stop(false) {
		for (unsigned int i = 0; i < N; ++i)
			threads[ i ] = std::move( std::thread( [&](){ thread_routine(); } ) );
	}
	catch (const std::exception& e) {
		logger::out("error: ", e.what(), endl);
		stop();
		pool_exception();
	}
	catch (...) {
		logger::out("unknown mistake", endl );
		stop();
		pool_exception();
	}

	~thread_pool() {
		stop();
	}

	void stop() {
		if (!_stop) {
			{
				std::unique_lock<std::mutex> _(mtx);
				_stop = true;
				cv.notify_all();
			}
			for (unsigned int i = 0; i < N; ++i)
				if( threads[i].joinable() )
					threads[i].join();
		}
	}

	void execute(function_t value) {
		std::unique_lock<std::mutex> _(mtx);
		if (!_stop) {
			queue.add( value );
			cv.notify_one();
		}
	}

private:

	typedef cache_queue<function_t> storage_t;

private:

	void thread_routine() {
		int count = 0;
		try {
			storage_t::value_t f;
			while( !_stop || !queue.empty() ) {
				{
					std::unique_lock<std::mutex> _(mtx);
					while (!_stop && queue.empty())
						cv.wait(_);
					if (queue.empty())
						continue;
					f.swap(queue.front());
					queue.store_front();
				}
				++count;
				if( f )
					execute_internal(f);
			}
		}
		catch( const std::exception& e ) {
			std::cerr << e.what() << std::endl;
		}
		logger::out( "stop: ", __FUNCTION__, " task count: ", count, " thread id: ", std::this_thread::get_id(), endl );
	}

	void execute_internal(function_t value) {
		try {
			value();
		}
		catch (const std::exception& e) {
			logger::out( __FUNCTION__, " error: ", e.what(), endl );
		}
		catch (...) {
			logger::out( __FUNCTION__, " unknown error.", endl );
		}
	}

	static void pool_exception() {
		throw(std::runtime_error("thread_pool exception."));
	}

private:

	bool _stop;
	storage_t queue;
	std::mutex mtx;
	std::condition_variable cv;
	std::thread threads[ N ];

};

