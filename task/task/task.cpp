// task.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <tuple>
#include <algorithm>
#include <memory>

#include "task.hpp"

//using factorial_type = std::function<int(int)>;

int fact(int value)
{
	int res = 1;
	while (value)
		res *= value--;
	return res;
}

void fact1(int value, int* res)
{
	*res = 1;
	while (value)
		*res *= value--;
}

struct a_type{};

int main()
{
	auto f = std::make_shared<a_type>();
	try
	{
		int res;
		lib::detail::invoke(&fact1, std::make_tuple(6, &res));
		lib::task< std::function<int(int)>, int> t;
		t.m_function = &fact;
		t.m_arguments = std::make_tuple(7);
		t.invoke();
		std::cout << t.m_result << std::endl;
#if 1
		lib::task< std::function<void(int,int*)>, int, int*> t1;
		t1.m_function = &fact1;
		t1.m_arguments = std::make_tuple(8,&res);
		t1.invoke();
		std::cout << res << std::endl;
#endif
		auto t2 = lib::make_task(&fact, 10);
//		std::cout << t1.m_result << std::endl;

		std::cout << lib::detail::invoke(&fact, std::make_tuple(5)) << " " <<
			res	<< std::endl;
		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

