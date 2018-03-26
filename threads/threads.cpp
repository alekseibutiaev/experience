#include <iostream>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <ctime>
#include <iterator>
#include <list>
#include <chrono>
#include <vector>

namespace std_cxx17 {
	// this function will by appeared only C++17, but MSVC 14.0 has this function.
	// it was wrote for c++11 compiler
	template< typename type, std::size_t n >
	std::size_t size(const type(&)[n]) { return n; }
}; /* namespace std_cxx17 */

const char* endl = "\n\r";

class logger {
public:

	logger() try : _stop(false), th([&]() { out_tread(); }) {
	}
	catch (const std::exception& e) {
		std::cerr << "error: " << e.what() << std::endl;
		stop();
		throw(std::runtime_error("log exception."));;
	}
	catch (...) {
		std::cerr << "unknown mistake" << std::endl;
		stop();
		throw(std::runtime_error("log exception."));;
	}

	~logger() {
		stop();
	}

	void stop() {
		if (th.joinable()) {
			{
				std::unique_lock<std::mutex> _(mtx);;
				_stop = true;
				cv.notify_one();
			}
			th.join();
			std::cerr << "log stop" << std::endl;
		}
	}

	void out(const std::string& value) {
		std::unique_lock<std::mutex> _(mtx);
		if( node_cache.empty() )
			queue.emplace_front(value);
		else {
			queue.splice(queue.begin(), node_cache, node_cache.begin());
			queue.front() = std::move(value);
		}
		cv.notify_one();
	}

private:
	typedef std::list<std::string> queue_t;
private:
	void out_tread() {
		try {
			queue_t local;
			while ( !_stop || !queue.empty() ) {
				{
					std::unique_lock<std::mutex> _(mtx);
					while (!_stop && queue.empty())
						cv.wait(_);
					local.swap(queue);
				}
				std::copy(local.begin(), local.end(), std::ostream_iterator<std::string>(std::cout));
				std::unique_lock<std::mutex> _(mtx);
				node_cache.splice(node_cache.end(), local);
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
private:
	bool _stop;
	queue_t queue;
	queue_t node_cache;
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
			threads.emplace_back(std::thread([&]() { thread_routine(); }));
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
			if (node_cache.empty())
				queue.emplace_front(value);
			else {
				queue.splice(queue.begin(), node_cache, node_cache.begin());
				queue.front() = std::move(value);
			}
			cv.notify_one();
		}
	}

private:

	void thread_routine() {
		int count = 0;
		try {
			function_t f;
			while( !_stop || !queue.empty() ) {
				{
					std::unique_lock<std::mutex> _(mtx);
					while (!_stop && queue.empty())
						cv.wait(_);
					if (queue.empty())
						continue;
					f.swap(queue.back());
					node_cache.splice(node_cache.end(), queue, --queue.end());
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
	typedef std::list<function_t> queue_t;
private:
	bool _stop;
	queue_t queue;
	queue_t node_cache;
	std::mutex mtx;
	std::condition_variable cv;
	std::vector<std::thread> threads;
};

typedef std::function<void(int, int, int)> func_t;

const func_t functions[] = {
	{ [](int ct, int lv, int rv) {
	out("counter: ", ct, ' ', lv, " + ", rv, " = ", lv + rv, endl); } },
	{ [](int ct, int lv, int rv) {
		out("counter: ", ct, ' ', lv, " - ", rv, " = ", lv - rv, endl); } },
		{ [](int ct, int lv, int rv) {
			out("counter: ", ct, ' ', lv, " * ", rv, " = ", lv * rv, endl); } },
			{ [](int ct, int lv, int rv) {
				if (0 == rv)
					throw(std::invalid_argument("devide by zero."));
				out("counter: ", ct, ' ', lv, " / ", rv, " = ", lv / rv, endl); } },
				{ [](int ct, int lv, int rv) {
					if (0 == rv)
						throw(std::invalid_argument("devide by zero."));
					out("counter: ", ct, ' ', lv, " % ", rv, " = ", lv % rv, endl); } },
};

struct stop_cond_t {
	int count;
	std::mutex mtx;
};

inline int my_rand(int limit) {
	return rand() % limit;
}

template< unsigned int N >
void producer(thread_pool<N>& pool, stop_cond_t& cond, const int id) {
	int count = 0;
	for (;;) {
		const func_t& func = functions[my_rand(static_cast<int>(std_cxx17::size(functions)))];
		const int lvalue = my_rand(1000);
		const int rvalue = my_rand(1000);
		int c;
		{
			std::unique_lock<std::mutex> _(cond.mtx);
			c = cond.count;
			if (0 == cond.count)
				break;
			else
				--cond.count;
		}
		pool.execute([c, lvalue, rvalue, func]() { func(c, lvalue, rvalue); });
		std::this_thread::sleep_for(std::chrono::milliseconds(my_rand((id + 1) * 100)));
		++count;
	}
	out("stop: ", __FUNCTION__, " loop count: ", count, " thread index: ", id, endl);
}


template< unsigned int N >
void start_producer(thread_pool<N>& pool) {
	const unsigned int producer_counter = 10;
	stop_cond_t conditional;
	conditional.count = 100;
	std::vector<std::thread> producers;
	for (unsigned int i = 0; i < producer_counter; ++i)
		producers.emplace_back(std::thread([&pool, &conditional, i]() { producer(pool, conditional, i); }));
	for (unsigned int i = 0; i < producer_counter; ++i)
		producers[i].join();
}

int main()
{
	int res = 0;
	out(__DATE__, ' ', __TIME__, endl);
	const logger& test = *mylog;
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

