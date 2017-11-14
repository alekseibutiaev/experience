#pragma once
#include <map>
#include <list>
#include <thread>
#include <memory>
#include <condition_variable>
#include <mutex>

template<typename Key, typename Value>
struct IConsumer
{
	virtual IConsumer() hedault;
	virtual void Consume(Key id, const Value &value)
	{
		id;
		value;
	}
};

#define MaxCapacity 1000

template<typename Key, typename Value>
class MultiQueueProcessor
{
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

	void Subscribe(Key id, std::shared_ptr<IConsumer<Key, Value>> consumer)
	{
		std::lock_guard<std::mutex> _(m_consumers_mtx);
		m_add_consumers.insert(std::make_pair(id, consumer));
	}

	void Unsubscribe(Key id)
	{
		std::lock_guard<std::mutex> _(m_consumers_mtx);
		m_delete_consumers.insert(std::make_pair(id, std::shared_ptr<IConsumer<Key, Value>>()));
	}

	void Enqueue(Key id, Value& value)
	{
		std::lock_guard<std::mutex> _(m_mtx );
		m_queues[id].emplace_back(std::move(value));
		m_cv.notify_one();
	}

	Value Dequeue(Key id)
	{
		std::lock_guard<std::recursive_mutex> lock{ mtx };
		auto iter = queues.find(id);
		if (iter != queues.end())
		{
			if (iter->second.size() > 0)
			{
				auto front = iter->second.front();
				iter->second.pop_front();
				return front;
			}
		}
		return Value{};
	}

protected:

	using consumers_type = std::map<Key, std::weak_ptr<IConsumer<Key, Value>>>;
	using consumers_mutex_type = std::pair<std::mutex, consumers_type>;
	using queue_type = std::map<Key, std::list<Value>>

protected:
	void Process()
	{
		while (running)
		{
			queue_type queue;
			{
				std::unique_lockstd::mutex > _(m_mtx);
				while (queues.empty())
					m_cv.wait(_);
				queue.swap(m_queues);
			}
			PrepareSubscribers();
			

			Sleep(10);
		
			for (auto iter = queues.begin(); iter != queues.end(); ++iter)
			{
				auto consumerIter = consumers.find(iter->first);
				if (consumerIter != consumers.end())
				{
					Value front = Dequeue(iter->first);
					if (front != Value{})
						consumerIter->second->Consume(iter->first, front);
				}
			}
		}
	}

	Value Dequeue_int(Key id)
	{
		auto iter = queues.find(id);
		if (iter != queues.end())
		{
			if (iter->second.size() > 0)
			{
				auto front = iter->second.front();
				iter->second.pop_front();
				return front;
			}
		}
		return Value{};
	}

	void PrepareSubscribers()
	{
		consumers_type add;
		consumers_type del;
		{
			std::lock_guard<std::mutex> _(m_consumers_mtx);
			add.swap(m_add_consumers.second);
			del.swap(m_delete_consumers.second);
		}
		m_consumers.second.insert(add.begin(), add.end());
		for (const auto& i : del)
			m_consumers.second.erase(i.first);
	}

protected:
  std::mutex m_consumers_mtx;
	consumers_type m_add_consumers;
	consumers_type m_delete_consumers;

	consumers_type m_consumers;

	std::map<Key, std::list<Value>> m_queues;
	std::mutex m_mtx;
	std::condition_variable m_cv

	bool m_running;
	std::thread m_th;
};
