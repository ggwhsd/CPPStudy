#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void initiazer(std::promise<int>* promObj,std::promise<char>* promObj2){
	std::cout<<"Inside Thread\n promise.set_value"<<std::endl;
	promObj->set_value(35);
//	std::this_thread::sleep_for(std::chrono::seconds(5));
	promObj2->set_value('a');
}

int main(){
	std::promise<int> promiseObj;
	std::promise<char> promiseObj2;
	std::future<int> futureObj = promiseObj.get_future();
	std::future<char> futureObj2 = promiseObj2.get_future();
	std::cout<<"begin create thread"<<std::endl;
	std::thread th(initiazer,&promiseObj,&promiseObj2);
	std::cout<<"future.get()"<<std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout<<futureObj.get()<<std::endl;
	std::cout<<futureObj2.get()<<std::endl;
	std::cout<<"will join to wait thread exit successfully"<<std::endl;
	th.join();
	return 0;
}
