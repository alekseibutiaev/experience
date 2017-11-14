#pragma once
#include <map>
#include <list>
#include <thread>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <boost/circular_buffer.hpp>

template<typename Key, typename Value>
struct IConsumer
{
	virtual ~IConsumer() = default;
	virtual void Consume(Key id, const Value &value)
	{
		id;
		value;
	}
};

const std::size_t MaxCapacity = 1000;

template<typename Key, typename Value>
class MultiQueueProcessor
{
public:
	using ConsumerPtr = std::shared_ptr<IConsumer<Key, Value>>;
public:
	MultiQueueProcessor()
		: m_running{ true }
		, m_th(std::bind(&MultiQueueProcessor::Process, this))
	{}

	~MultiQueueProcessor()
	{
		StopProcessing();
	}

	void StopProcessing()
	{
		if (m_th.joinable())
		{
			m_running = false;
			m_th.join();
		}
	}

	void Subscribe(const Key& id, ConsumerPtr consumer)
	{
		std::lock_guard<std::mutex> _(m_consumers_mtx);
		m_add_consumers.insert(std::make_pair(id, consumer));
	}

	void Unsubscribe(Key id)
	{
		std::lock_guard<std::mutex> _(m_consumers_mtx);
		m_delete_consumers.insert(std::make_pair(id, ConsumerPtr()));
	}

	void Enqueue(const Key& id, const Value& value)
	{
		std::lock_guard<std::mutex> _(m_mtx);
		auto it = m_queues.find(id);
		if (it == m_queues.end())
			it = m_queues.emplace(id, boost::circular_buffer<Value>(MaxCapacity)).first;
		if (!it->second.full())
		{
			it->second.push_back(value);
			m_cv.notify_one();
		}
	}

protected:

	using queue_buffer_type = boost::circular_buffer<Value>;
	using consumers_type = std::map<Key, std::weak_ptr<IConsumer<Key, Value>>>;
	using queue_type = std::map<Key, queue_buffer_type>;

protected:
	void Process()
	{
		queue_type queue;
		while (m_running)
		{
			{
				std::unique_lock<std::mutex > _(m_mtx);
				while (m_queues.empty())
					m_cv.wait(_);
				if (!m_running)
					break;
				queue.swap(m_queues);
			}
			PrepareSubscribers();
			PrepareQueue(queue);
		}
	}

	void PrepareQueue(queue_type& queue)
	{
		for (auto& i : queue)
		{
			auto consumerIter = m_consumers.find(i.first);
			if (consumerIter == m_consumers.end())
				continue;
			if (ConsumerPtr c = consumerIter->second.lock())
			{
				for (const auto& bi : i.second)
					c->Consume(i.first, bi);
				i.second.clear();
			}
		}
	}

	void PrepareSubscribers()
	{
		consumers_type add;
		consumers_type del;
		{
			std::lock_guard<std::mutex> _(m_consumers_mtx);
			add.swap(m_add_consumers);
			del.swap(m_delete_consumers);
		}
		m_consumers.insert(add.begin(), add.end());
		for (const auto& i : del)
			m_consumers.erase(i.first);
	}

protected:
  std::mutex m_consumers_mtx;
	consumers_type m_add_consumers;
	consumers_type m_delete_consumers;

	consumers_type m_consumers;

	queue_type m_queues;
	std::mutex m_mtx;
	std::condition_variable m_cv;

	bool m_running;
	std::thread m_th;
};
