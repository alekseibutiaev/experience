#pragma once
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <algorithm>
#include <condition_variable>
#include <boost/circular_buffer.hpp>

namespace exn
{

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

	template<typename Key, typename Value, std::size_t Max = 1000>
	class MultiQueueProcessor
	{
	public:

		static const std::size_t MaxCapacity = Max;
		using this_type = MultiQueueProcessor<Key, Value, Max>;
		using consumer_type = IConsumer<Key, Value>;
		using consumer_ptr = std::shared_ptr<consumer_type>;

	public:

		MultiQueueProcessor()
			: m_running{ true }
		{
		}

		~MultiQueueProcessor()
		{
			StopProcessing();
		}

		void StartProcessing()
		{
			m_th = std::thread(std::bind(&MultiQueueProcessor::Process, this));
		}

		void StopProcessing()
		{
			if (m_th.joinable())
			{
				m_running = false;
				m_cv.notice_one();
				m_th.join();
			}
		}

		void Subscribe(const Key& id, consumer_ptr consumer)
		{
			std::lock_guard<std::mutex> _(m_consumers_mtx);
			m_subscribe_consumers.insert(std::make_pair(id, consumer));
			m_unsubscribe_consumers.erase(id);
		}

		void Unsubscribe(Key id)
		{
			std::lock_guard<std::mutex> _(m_consumers_mtx);
			m_unsubscribe_consumers[id];
			m_subscribe_consumers.erase(id);
		}

		void Enqueue(const Key& id, const Value& value)
		{
			std::lock_guard<std::mutex> _(m_mtx);
			auto it = m_queues.find(id);
			if (it == m_queues.end())
			{
				it = m_queues.emplace(id, GetCircularBuffer()).first;
			}
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
		using buffers_storage_type = std::list<queue_buffer_type>;
		using keys_type = std::vector<Key>;

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
				const keys_type unavailable_consumers = std::move(PrepareQueue(queue));
				DeleteUnavailableConsumer(queue, unavailable_consumers);
			}
		}

		keys_type PrepareQueue(queue_type& queue)
		{
			keys_type unavailable_consumers;
			unavailable_consumers.reserve(queue.size());
			for (auto& i : queue)
			{
				auto consumerIter = m_consumers.find(i.first);
				if (consumerIter != m_consumers.end())
				{
					if (consumer_ptr c = consumerIter->second.lock())
					{
						CallConsumer(i, c);
						continue;
					}
				}
				unavailable_consumers.push_back(i.first);
			}
			return unavailable_consumers;
		}

		void CallConsumer(typename queue_type::value_type& queue_element, consumer_ptr consumer)
		{
			for (const auto& data : queue_element.second)
				consumer->Consume(queue_element.first, data);
			queue_element.second.clear();
		}

		void StoreBuffer(queue_buffer_type&& bufer)
		{
			bufer.clear();
			std::lock_guard<std::mutex> _(m_consumers_mtx);
			m_buffers_storage.emplace_back(std::move(bufer));
		}

		void DeleteUnavailableConsumer(queue_type& queue, const keys_type& unavailable_consumers)
		{
			this_type& tmp = *this;
			std::for_each(unavailable_consumers.begin(), unavailable_consumers.end(),
				[&tmp, &queue](const Key& key) {
					tmp.StoreBuffer(std::move(queue[key]));
					queue.erase(key);
				}
			);
		}

		void PrepareSubscribers()
		{
			consumers_type subscribe;
			consumers_type unsubscribe;
			{
				std::lock_guard<std::mutex> _(m_consumers_mtx);
				subscribe.swap(m_subscribe_consumers);
				unsubscribe.swap(m_unsubscribe_consumers);
			}
			m_consumers.insert(subscribe.begin(), subscribe.end());
			for (const auto& i : unsubscribe)
				m_consumers.erase(i.first);
		}

		queue_buffer_type GetCircularBuffer()
		{
			if (m_buffers_storage.empty())
				return queue_buffer_type(MaxCapacity);
			else
			{
				queue_buffer_type tmp = std::move(m_buffers_storage.front());
				m_buffers_storage.pop_front();
				return tmp;
			}
		}

	protected:

		std::mutex m_consumers_mtx;
		consumers_type m_subscribe_consumers;
		consumers_type m_unsubscribe_consumers;
		buffers_storage_type m_buffers_storage;

		consumers_type m_consumers;

		queue_type m_queues;
		std::mutex m_mtx;
		std::condition_variable m_cv;

		bool m_running;
		std::thread m_th;

	};

} /* namespace exn */

