#include <string>
#include <boost/align.hpp>
#include "MultiQueueProcessor.h"

using MultiQueueProcessor_type = exn::MultiQueueProcessor<int, std::string>;

//class 

int main()
{
	MultiQueueProcessor_type mq;
	mq.Enqueue(10, "jhsdfhgjk");
  return 0;
}

