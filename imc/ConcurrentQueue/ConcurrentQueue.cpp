#include <cmath>
#include <functional>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

template<typename T, uint64_t SIZE = 4096, uint64_t MAX_SPIN_ON_BUSY = 40000000>
class ConcurrentQueue {
private:
	static constexpr unsigned Log2(unsigned n, unsigned p = 0) {
		return (n <= 1) ? p : Log2(n / 2, p + 1);
	}

	static constexpr uint64_t closestExponentOf2(uint64_t x) {
		return (1UL << ((uint64_t)(Log2(SIZE - 1)) + 1));
	}

	static constexpr uint64_t mSize = closestExponentOf2(SIZE);

	static const T mEmpty;

	T mMem[mSize];
	std::mutex mLock;
	std::atomic_uint64_t mReadPtr = 0;
	std::atomic_uint64_t mWritePtr = 0;

public:

	void pop( T& r ) {
		std::lock_guard<std::mutex> lock(mLock);

		if (!peek()) {
			r = std::move(mEmpty);
			return;
		}

		r = std::move( mMem[mReadPtr % mSize]);
		mReadPtr++;
		return;
	}

	bool peek() const {
		return (mWritePtr != mReadPtr);
	}

	uint64_t getCount() const {
		return mWritePtr > mReadPtr ? mWritePtr - mReadPtr : mReadPtr - mWritePtr;
	}

	bool busyWaitForPush() {
		uint64_t start = 0;
		while (getCount() == mSize) {
			if (start++ > MAX_SPIN_ON_BUSY) {
				return false;
			}
		}
		return true;
	}

	void push(const T& pItem) {
		if (!busyWaitForPush()) {
			throw std::runtime_error("Concurrent queue full cannot write to it!");
		}

		std::lock_guard<std::mutex> lock(mLock);
		mMem[mWritePtr % mSize] = pItem;
		mWritePtr++;
	}

	void push_(T&& pItem) {
		if (!busyWaitForPush()) {
			throw std::runtime_error("Concurrent queue full cannot write to it!");
		}

		std::lock_guard<std::mutex> lock(mLock);
		mMem[mWritePtr % mSize] = std::move(pItem);
		mWritePtr++;
	}
};

template<typename T, uint64_t SIZE, uint64_t MAX_SPIN_ON_BUSY>
const T ConcurrentQueue<T, SIZE, MAX_SPIN_ON_BUSY>::mEmpty = T{};

int main(int, char**) {
	try
	{
		using Functor = std::function<void()>;

		ConcurrentQueue<Functor> queue;

		std::thread consumer([&] {
			try {
				while (true) {
					if (queue.peek()) {
						Functor task;
						queue.pop(task);
						if (task)
							(task)();
					}
				}
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		});

		std::thread producer([&] {
			uint64_t counter = 0;
			while (true) {
				try {
					auto taskId = counter++;
					queue.push_(Functor([taskId] {
						std::cout << "Running task " << taskId << std::endl << std::flush;
//						std::this_thread::sleep_for(std::chrono::milliseconds(100)); // for test
					}));
				}
				catch (const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
		}
		);

		consumer.join();
		producer.join();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
