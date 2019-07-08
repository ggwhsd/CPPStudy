#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <functional>

int countdown(int from, int to)
{
	for(int i = from; i!= to; --i)
	{
		std::cout<< i << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout<<"Lift off!\n";
	return from - to;
}

int main()
{
	std::packaged_task<int(int,int)> tsk(countdown);
	std::future<int> ret = tsk.get_future();
	std::cout<<"pacaged_task in thread\n";
	std::thread th(std::move(tsk),10,0);
	//std::thread th(std::ref(tsk),10,0);

	std::cout<<"future.get()"<<std::endl;
	int value = ret.get();
	std::cout<<"thread join()"<<std::endl;
	std::cout<<"last value "<<value<<std::endl;
	th.join();
}


