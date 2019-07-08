#pragma once
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <functional>

int countdown(int from, int to)
{
	for (int i = from; i != to; --i)
	{
		std::cout << i << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Lift off!\n";
	return from - to;
}
\
class TEST
{
public:
	int countdown(int from, int to)
	{
		for (int i = from; i != to; --i)
		{
			std::cout << i << "\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "Lift off!\n";
		return from - to;
	}
};

void packagedTask_test()
{
	std::packaged_task<int(int, int)> tsk(countdown);
	std::future<int> ret = tsk.get_future();
	std::cout << "pacaged_task in thread\n";
	std::thread th(std::move(tsk), 10, 0);
	//std::thread th(std::ref(tsk),10,0);

	std::cout << "future.get()" << std::endl;
	int value = ret.get();
	std::cout << "thread join()" << std::endl;
	std::cout << "last value " << value << std::endl;
	th.join();
}


void packagedTask_testBind()
{
	std::packaged_task<int()> tsk(std::bind(countdown,10,0));
	std::future<int> ret = tsk.get_future();
	std::cout << "pacaged_task in thread\n";
	//std::thread th(std::move(tsk), 10, 0);
	//std::thread th(std::ref(tsk),10,0);
	std::thread th(std::move(tsk));


	std::cout << "future.get()" << std::endl;
	int value = ret.get();
	std::cout << "thread join()" << std::endl;
	std::cout << "last value " << value << std::endl;
	th.join();
}

void packagedTask_testBindholder()
{
	std::packaged_task<int(int,int)> tsk(std::bind(countdown, placeholders::_1, placeholders::_2));
	std::future<int> ret = tsk.get_future();
	std::cout << "pacaged_task in thread\n";
	//std::thread th(std::move(tsk), 10, 0);
	//std::thread th(std::ref(tsk),10,0);
	std::thread th(std::ref(tsk),10,0);


	std::cout << "future.get()" << std::endl;
	int value = ret.get();
	std::cout << "thread join()" << std::endl;
	std::cout << "last value " << value << std::endl;
	th.join();
}


void packagedTask_testClassBindholder()
{
	TEST tt;
	std::packaged_task<int(int, int)> tsk(std::bind(&TEST::countdown, &tt, placeholders::_1, placeholders::_2));
	std::future<int> ret = tsk.get_future();
	std::cout << "pacaged_task in thread\n";
	//std::thread th(std::move(tsk), 10, 0);
	//std::thread th(std::ref(tsk),10,0);
	std::thread th(std::move(tsk), 10, 0);


	std::cout << "future.get()" << std::endl;
	int value = ret.get();
	std::cout << "thread join()" << std::endl;
	std::cout << "last value " << value << std::endl;
	th.join();
}

