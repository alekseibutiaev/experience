#include <list>
#include <mutex>
#include <ctime>
#include <chrono>
#include <atomic>
#include <vector>
#include <iostream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <thread>
#include <condition_variable>
#include <functional>
#include <iterator>

namespace std_cxx17 {

	// this function will by appeared only C++17, but MSVC 14.0 has this function now.
	// it was wrote for support c++11 compiler 
	template< typename type, std::size_t n >
	std::size_t size(const type(&)[n]) { return n; }

}; /* namespace std_cxx17 */

const char* endl = "\n\r";
const unsigned int producer_counter = 10;
const long long max_task = 100;

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

	logger() try : _stop(false), th([&](){ out_tread(); }) {
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

	void out(const std::string& value) {
		std::unique_lock<std::mutex> _(mtx);
		queue.add(value);
		cv.notify_one();
	}

private:

	typedef cache_queue<std::string> storage_t;

private:

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

};

std::unique_ptr<logger> mylog;

void out(std::stringstream& stream) {
	if (!mylog)
		mylog.reset(new logger());
	mylog->out(stream.str());
}

template <typename type1_t, typename... types_t >
void out(std::stringstream& stream, const type1_t& value, const types_t&... values) {
	stream << value;
	out(stream, values...);
}

template <typename type1_t, typename... types_t >
void out(const type1_t& value, const types_t&... values) {
	std::stringstream stream;
	stream << value;
	out(stream, values...);
}

template< unsigned int N >
class thread_pool {
public:

	typedef std::function<void()> function_t;

public:

	thread_pool() try : _stop(false) {
		for (unsigned int i = 0; i < N; ++i)
			threads.emplace_back([&]() { thread_routine(); });
	}
	catch (const std::exception& e) {
		out("error: ", e.what(), endl);
		stop();
		pool_exception();
	}
	catch (...) {
		out("unknown mistake", endl );
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
				execute_internal(f);
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		out("stop: ", __FUNCTION__, " task count: ", count, " thread id: ", std::this_thread::get_id(), endl);
	}

	void execute_internal(function_t value) {
		if (value) {
			try {
				value();
			}
			catch (const std::exception& e) {
				out(__FUNCTION__, " error: ", e.what(), endl);
			}
			catch (...) {
				out(__FUNCTION__, " unknown error.", endl);
			}
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
	std::vector<std::thread> threads;

};

inline void devide_by_zero( int ct, int value ) {
	if (0 == value)
		throw(std::invalid_argument("counter: " + std::to_string(ct) + ", devide by zero."));
}

typedef std::function<void(int, int, int)> func_t;

const func_t functions[] = {
	{ [](int ct, int lv, int rv) {
		out("counter: ", ct, ' ', lv, " + ", rv, " = ", lv + rv, endl); }
	},
	{ [](int ct, int lv, int rv) {
		out("counter: ", ct, ' ', lv, " - ", rv, " = ", lv - rv, endl); }
	},
	{ [](int ct, int lv, int rv) {
		out("counter: ", ct, ' ', lv, " * ", rv, " = ", lv * rv, endl); }
	},
	{ [](int ct, int lv, int rv) {
		devide_by_zero(ct, rv);
		out("counter: ", ct, ' ', lv, " / ", rv, " = ", lv / rv, endl); }
	},
	{ [](int ct, int lv, int rv) {
		devide_by_zero(ct, rv);
		out("counter: ", ct, ' ', lv, " % ", rv, " = ", lv % rv, endl); }
	},
};

inline int my_rand(int limit) {
	return rand() % limit;
}

template< unsigned int N >
void producer(thread_pool<N>& pool, std::atomic_llong& conditional, const int id) {
	int count = 0;
	for ( int c = 0; (c = --conditional) >= 0; ) {
		const func_t& func = functions[my_rand(static_cast<int>(std_cxx17::size(functions)))];
		const int lvalue = my_rand(1000);
		const int rvalue = my_rand(1000);
		pool.execute([c, lvalue, rvalue, func](){ func(c, lvalue, rvalue); });
		std::this_thread::sleep_for(std::chrono::milliseconds(my_rand((id + 1) * 100)));
		++count;
	}
	out("stop: ", __FUNCTION__, " loop count: ", count, " thread index: ", id, endl);
}


template< unsigned int N >
void start_producer(thread_pool<N>& pool) {
    std::atomic_llong conditional(max_task);
	std::vector<std::thread> producers;
	for (unsigned int i = 0; i < producer_counter; ++i)
		producers.emplace_back([&pool, &conditional, i](){ producer(pool, conditional, i); });
	for (unsigned int i = 0; i < producer_counter; ++i)
		producers[i].join();
}

int main()
{
	int res = 0;
	out(__DATE__, ' ', __TIME__, endl);
	{
		try {
			srand(static_cast<unsigned int>(time(NULL)));
			thread_pool<5> tp;
			start_producer(tp);
			tp.stop();
			out("stop: ", __FUNCTION__, ' ', endl);
		}
		catch (const std::exception& e) {
			out(e.what(), endl);
			res = -1;
		}
		catch (...) {
			out("unknown mistake", endl);
			res = -1;
		}
		if (mylog)
			mylog->stop();
	}
	return res;
}

