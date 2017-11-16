#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <MultiQueueProcessor/MultiQueueProcessor.h>

namespace ut
{

	using MultiQueueProcessorType = exn::MultiQueueProcessor<int, std::string>;

	struct TypeAccessor : MultiQueueProcessorType
	{
		using MultiQueueProcessorType::Consumer;
		using MultiQueueProcessorType::ConsumerPtr;
		using MultiQueueProcessorType::queue_buffer_type;
		using MultiQueueProcessorType::consumers_type;
		using MultiQueueProcessorType::queue_type;
		using MultiQueueProcessorType::buffers_storage_type;

		using MultiQueueProcessorType::StopProcessing;
		using MultiQueueProcessorType::Subscribe;
		using MultiQueueProcessorType::Unsubscribe;
		using MultiQueueProcessorType::Enqueue;
		using MultiQueueProcessorType::Process;
		using MultiQueueProcessorType::PrepareQueue;
		using MultiQueueProcessorType::StoreBuffer;
		using MultiQueueProcessorType::PrepareSubscribers;
		
		using MultiQueueProcessorType::m_add_consumers;
		using MultiQueueProcessorType::m_delete_consumers;
		using MultiQueueProcessorType::m_buffers_storage;
		using MultiQueueProcessorType::m_consumers;
		using MultiQueueProcessorType::m_queues;
		using MultiQueueProcessorType::m_mtx;
		using MultiQueueProcessorType::m_cv;
		using MultiQueueProcessorType::m_running;
		using MultiQueueProcessorType::m_th;

	};

	struct TestConsumer : TypeAccessor::Consumer
	{
		void Consume(int id, const std::string& value) override
		{}
	};


} /* namespace ut */


BOOST_AUTO_TEST_SUITE(TestConsumer)

BOOST_AUTO_TEST_CASE(ConsumerMonitulation) {
	ut::TypeAccessor mqp;
	auto consumer = std::make_shared<ut::TestConsumer>();
	mqp.Subscribe(10, consumer);
	BOOST_REQUIRE(mqp.m_add_consumers.find(10) != mqp.m_add_consumers.end());
	mqp.PrepareSubscribers();
	BOOST_REQUIRE(mqp.m_add_consumers.empty());
	BOOST_REQUIRE(mqp.m_consumers.find(10) != mqp.m_consumers.end());
	mqp.Unsubscribe(10);
	BOOST_REQUIRE(mqp.m_delete_consumers.find(10) != mqp.m_delete_consumers.end());
	mqp.PrepareSubscribers();
	BOOST_REQUIRE(mqp.m_delete_consumers.empty());
	BOOST_REQUIRE(mqp.m_consumers.empty());
}

BOOST_AUTO_TEST_CASE(DeleteConsumer) {

}


BOOST_AUTO_TEST_SUITE_END()

