#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <MultiQueueProcessor/MultiQueueProcessor.h>

namespace ut
{

	using MultiQueueProcessorType = exn::MultiQueueProcessor<int, std::string, 5>;

	struct TypeAccessor : MultiQueueProcessorType
	{
		using MultiQueueProcessorType::MaxCapacity;
		using MultiQueueProcessorType::consumer_type;
		using MultiQueueProcessorType::consumer_ptr;
		using MultiQueueProcessorType::queue_buffer_type;
		using MultiQueueProcessorType::consumers_type;
		using MultiQueueProcessorType::queue_type;
		using MultiQueueProcessorType::buffers_storage_type;
		using MultiQueueProcessorType::keys_type;

		using MultiQueueProcessorType::StopProcessing;
		using MultiQueueProcessorType::Subscribe;
		using MultiQueueProcessorType::Unsubscribe;
		using MultiQueueProcessorType::Enqueue;
		using MultiQueueProcessorType::Process;
		using MultiQueueProcessorType::PrepareQueue;
		using MultiQueueProcessorType::StoreBuffer;
		using MultiQueueProcessorType::PrepareSubscribers;
		using MultiQueueProcessorType::GetCircularBuffer;
		using MultiQueueProcessorType::DeleteUnavailableConsumer;
		
		using MultiQueueProcessorType::m_subscribe_consumers;
		using MultiQueueProcessorType::m_unsubscribe_consumers;
		using MultiQueueProcessorType::m_buffers_storage;
		using MultiQueueProcessorType::m_consumers;
		using MultiQueueProcessorType::m_queues;
		using MultiQueueProcessorType::m_mtx;
		using MultiQueueProcessorType::m_cv;
		using MultiQueueProcessorType::m_running;
		using MultiQueueProcessorType::m_th;

	};

	struct TestConsumer : TypeAccessor::consumer_type
	{
		int counter = 0;
		void Consume(int id, const std::string& value) override
		{
			++counter;
		}
	};

	struct TestConsumerOnePass : TypeAccessor::consumer_type
	{
		bool* m_running = 0;
		void Consume(int id, const std::string& value) override
		{
			*m_running = false;
		}
	};

	struct TestConsumerCondition : TypeAccessor::consumer_type
	{
		bool m_test = false;
		std::mutex m_mtx;
		std::condition_variable m_cv;
		void Consume(int id, const std::string& value) override
		{
			std::lock_guard<std::mutex> _(m_mtx);
			m_test = true;
			m_cv.notify_one();
		}
	};


} /* namespace ut */


BOOST_AUTO_TEST_SUITE(TestConsumer)

BOOST_AUTO_TEST_CASE(ConsumerManitulation) {

	ut::TypeAccessor mqp;
	auto consumer = std::make_shared<ut::TestConsumer>();

	mqp.Subscribe(10, consumer);
	BOOST_REQUIRE_MESSAGE(mqp.m_subscribe_consumers.find(10) != mqp.m_subscribe_consumers.end(),
		"the map of subscribe can not by empty");
	mqp.PrepareSubscribers();
	BOOST_REQUIRE_MESSAGE(mqp.m_subscribe_consumers.empty(),
		"the map of subscribe must by empty");
	BOOST_REQUIRE_MESSAGE(mqp.m_consumers.find(10) != mqp.m_consumers.end(),
		"the map of consumer must has a consumer");
	
	mqp.Unsubscribe(10);
	BOOST_REQUIRE_MESSAGE(mqp.m_unsubscribe_consumers.find(10) != mqp.m_unsubscribe_consumers.end(),
		"the map of unsubscribe can not by empty");
	mqp.PrepareSubscribers();
	BOOST_REQUIRE_MESSAGE(mqp.m_unsubscribe_consumers.empty(),
		"the map of unsubscribe must by empty");
	BOOST_REQUIRE_MESSAGE(mqp.m_consumers.empty(),
		"the map of consumer must by empty");

	mqp.Subscribe(15, consumer);
	mqp.PrepareSubscribers();
	BOOST_REQUIRE_MESSAGE(mqp.m_consumers.find(15) != mqp.m_consumers.end(),
		"the map of consumer must has a consumer");

	mqp.Subscribe(15, consumer);
	mqp.Unsubscribe(15);
	BOOST_REQUIRE_MESSAGE(mqp.m_subscribe_consumers.empty(),
		"the map of subscribe must by empty");
	BOOST_REQUIRE_MESSAGE(mqp.m_unsubscribe_consumers.find(15) != mqp.m_unsubscribe_consumers.end(),
		"the map of unsubscribe can not by empty");
	mqp.PrepareSubscribers();
	BOOST_REQUIRE_MESSAGE(mqp.m_consumers.empty(),
		"the map of consumer must by empty");

	mqp.Unsubscribe(15);
	mqp.Subscribe(15, consumer);
	BOOST_REQUIRE_MESSAGE(mqp.m_unsubscribe_consumers.empty(),
		"the map of unsubscribe must by empty");
	BOOST_REQUIRE_MESSAGE(mqp.m_subscribe_consumers.find(15) != mqp.m_subscribe_consumers.end(),
		"the map of subscribe can not by empty");
	mqp.PrepareSubscribers();
	BOOST_REQUIRE_MESSAGE(mqp.m_consumers.find(15) != mqp.m_consumers.end(),
		"the map of consumer must has a consumer");

}

BOOST_AUTO_TEST_CASE(StorageCircularBuffer) {

	ut::TypeAccessor mqp;

	BOOST_REQUIRE_MESSAGE(mqp.m_buffers_storage.empty(),
		"the storage of buffers must by empty");
	ut::TypeAccessor::queue_buffer_type tmp = std::move(mqp.GetCircularBuffer());
	BOOST_REQUIRE_MESSAGE(mqp.m_buffers_storage.empty(),
		"the storage of buffers must by empty");
	tmp.push_back(std::string());
	mqp.StoreBuffer(std::move(tmp));
	BOOST_REQUIRE_MESSAGE(!mqp.m_buffers_storage.empty(),
		"the storage of buffers can not by empty");
	tmp = std::move(mqp.GetCircularBuffer());
	BOOST_REQUIRE_MESSAGE(mqp.m_buffers_storage.empty(),
		"the storage of buffers must by empty");
	BOOST_REQUIRE_MESSAGE(tmp.empty(),
		"the buffer must by empty");
}

BOOST_AUTO_TEST_CASE(QueueManipulation)
{
	ut::TypeAccessor mqp;

	mqp.Enqueue(10, std::string());
	mqp.Enqueue(10, std::string());
	BOOST_REQUIRE_EQUAL(mqp.m_queues[10].size(), 2);
	for(std::size_t n = 0; n < ut::TypeAccessor::MaxCapacity; ++n )
		mqp.Enqueue(10, std::string());
	BOOST_REQUIRE_EQUAL(mqp.m_queues[10].size(), ut::TypeAccessor::MaxCapacity);

	mqp.Enqueue(15, std::string());
	mqp.Enqueue(20, std::string());
	BOOST_REQUIRE_EQUAL(mqp.m_queues.size(), 3);

	mqp.Enqueue(25, std::string());
	mqp.Enqueue(30, std::string());
	mqp.Enqueue(35, std::string());
	mqp.Enqueue(40, std::string());
	BOOST_REQUIRE_EQUAL(mqp.m_queues.size(), 7);

	{
		const ut::TypeAccessor::keys_type keys = { 25, 15, 35, 40 };
		mqp.DeleteUnavailableConsumer(mqp.m_queues, keys);
		BOOST_REQUIRE_EQUAL(mqp.m_queues.size(), 3);
		BOOST_REQUIRE_EQUAL(mqp.m_buffers_storage.size(), 4);
	}

	mqp.Enqueue(25, std::string());
	mqp.Enqueue(15, std::string());
	mqp.Enqueue(35, std::string());
	mqp.Enqueue(40, std::string());
	BOOST_REQUIRE_EQUAL(mqp.m_queues.size(), 7);

	ut::TypeAccessor::consumer_ptr consumer10 = std::make_shared<ut::TestConsumer>();
	ut::TypeAccessor::consumer_ptr consumer15 = std::make_shared<ut::TestConsumer>();
	ut::TypeAccessor::consumer_ptr consumer20 = std::make_shared<ut::TestConsumer>();
	ut::TypeAccessor::consumer_ptr consumer25 = std::make_shared<ut::TestConsumer>();
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer10)->counter, 0);
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer15)->counter, 0);
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer20)->counter, 0);
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer25)->counter, 0);

	{
		ut::TypeAccessor::consumer_ptr consumer30 = std::make_shared<ut::TestConsumer>();
		ut::TypeAccessor::consumer_ptr consumer35 = std::make_shared<ut::TestConsumer>();
		ut::TypeAccessor::consumer_ptr consumer40 = std::make_shared<ut::TestConsumer>();
		mqp.Subscribe(10, consumer10);
		mqp.Subscribe(15, consumer15);
		mqp.Subscribe(20, consumer20);
		mqp.Subscribe(25, consumer25);
		mqp.Subscribe(30, consumer30);
		mqp.Subscribe(35, consumer35);
		mqp.Subscribe(40, consumer40);
		mqp.PrepareSubscribers();
	}

	BOOST_REQUIRE_EQUAL(mqp.m_consumers.size(), 7);

	{
		const ut::TypeAccessor::keys_type keys = std::move(mqp.PrepareQueue(mqp.m_queues));
		BOOST_REQUIRE_EQUAL(keys.size(), 3);
		mqp.DeleteUnavailableConsumer(mqp.m_queues, keys);
	}
	BOOST_REQUIRE_EQUAL(mqp.m_queues.size(), 4);
	BOOST_REQUIRE_EQUAL(mqp.m_buffers_storage.size(), 3);
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer10)->counter, 5);
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer15)->counter, 1);
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer20)->counter, 1);
	BOOST_REQUIRE_EQUAL(std::static_pointer_cast<ut::TestConsumer>(consumer25)->counter, 1);

}

BOOST_AUTO_TEST_CASE(Process)
{
	ut::TypeAccessor mqp;
	BOOST_TEST(mqp.m_running, "Flag m_runner must bu true");
	auto consumer10 = std::make_shared<ut::TestConsumerOnePass>();
	std::static_pointer_cast<ut::TestConsumerOnePass>(consumer10)->m_running = &mqp.m_running;
	mqp.Subscribe(10, consumer10);
	BOOST_REQUIRE_MESSAGE(mqp.m_subscribe_consumers.find(10) != mqp.m_subscribe_consumers.end(),
		"the map of subscribe can not by empty");
	mqp.m_running = false;
	mqp.Process();
	BOOST_REQUIRE_MESSAGE(mqp.m_subscribe_consumers.find(10) != mqp.m_subscribe_consumers.end(),
		"the map of subscribe can not by empty");
	mqp.m_running = true;
	mqp.Enqueue(10, std::string());
	BOOST_REQUIRE_MESSAGE(!mqp.m_queues.empty(), "the m_queues can not by empty");
	mqp.Process();
	BOOST_REQUIRE_MESSAGE(mqp.m_subscribe_consumers.empty(),
		"the map of subscribe must by empty");
	BOOST_TEST(!*std::static_pointer_cast<ut::TestConsumerOnePass>(consumer10)->m_running);
	BOOST_REQUIRE_MESSAGE(mqp.m_queues.empty(), "the m_queues must by empty");

	mqp.m_running = true;
	ut::TypeAccessor::consumer_ptr consumer15 = std::make_shared<ut::TestConsumerCondition>();
	BOOST_TEST(!std::static_pointer_cast<ut::TestConsumerCondition>(consumer15)->m_test);

	mqp.Enqueue(15, std::string());
	mqp.Subscribe(15, consumer15);
	std::unique_lock<std::mutex> _(std::static_pointer_cast<ut::TestConsumerCondition>(consumer15)->m_mtx);
	mqp.StartProcessing();
	while (!std::static_pointer_cast<ut::TestConsumerCondition>(consumer15)->m_test)
		std::static_pointer_cast<ut::TestConsumerCondition>(consumer15)->m_cv.wait(_);
	mqp.Subscribe(10, consumer10);
	mqp.Enqueue(10, std::string());
	mqp.StopProcessing();
	BOOST_REQUIRE_MESSAGE(mqp.m_queues.empty(), "the m_queues must by empty");
	BOOST_REQUIRE_EQUAL(mqp.m_consumers.size(), 2);
}

BOOST_AUTO_TEST_SUITE_END()

