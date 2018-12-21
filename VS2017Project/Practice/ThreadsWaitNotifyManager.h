#pragma once
/*
	项目中多个线程之间有互相等待执行的依赖关系，但是由于有些线程是用的其他库接口中的功能创建，有些是我们自己开发创建。
	若线程互相依赖，原先的解决办法就是循环等待条件，间隔很短的sleep线程，然后继续检查条件是否满足。这种方式对于资源使用效率不高。
	现在打算使用条件变量，使得这些线程都集中到一起进行通信，将会提高资源使用效率。
*/
#include <thread>
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "./chronoStudy.h"
using namespace std;

class messenger
{

public:
	string wait()
	{
		string data("");
			unique_lock<mutex> lk(mut);
			//lk.unlock();
			
			cout << getSystemClock_microSeconds() << "before wait" << endl;
			data_cond.wait(lk, [this] {return !data_queue.empty(); });
			cout << getSystemClock_microSeconds()<<"after wait" << endl;
			if (!data_queue.empty())
			{
				cout << getSystemClock_microSeconds() << "get a message :" << (data = data_queue.back()).c_str() << endl;;
				data_queue.pop();
			}
			lk.unlock();
			return data;
		
	}

	void notify(string&& message)
	{
		this_thread::sleep_for(chrono::milliseconds(5000));
		lock_guard<mutex> lk(mut);
		data_queue.push(message);
		cout << getSystemClock_microSeconds() << "send a message"<< message.c_str() << endl;
		data_cond.notify_one();
		cout << getSystemClock_microSeconds() << "notify_one" << endl;

		

	}

	void init()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << getSystemClock_microSeconds() << "init" << endl;

	}

	
private:
	mutex mut;
	queue<string> data_queue;
	condition_variable data_cond;

};




class commander
{

public:
	void data_preparation_thread()
	{
		cout << getSystemClock_microSeconds() << __FUNCTION__ << "begin" << endl;
		mes->notify("hello");
		cout << getSystemClock_microSeconds() << __FUNCTION__ << "end" << endl;

	}

	void data_processing_thread()
	{
		cout << getSystemClock_microSeconds() << __FUNCTION__ << "begin"<<endl;
		string result = mes->wait();
		if (result.compare("")!=0)
		{
			cout << getSystemClock_microSeconds() << __FUNCTION__ <<"result "<< result.c_str() << endl;
		}
		cout << getSystemClock_microSeconds() << __FUNCTION__ << "end"<<endl;
	}

	void init()
	{
		
		
	

	}

	void setMessenger(messenger * m)
	{
		mes = m;
	}
	commander(string str)
	{
		name = str;
	}
private:
	string name;
	messenger * mes;
};

void messengerTest()
{
	messenger *mes = new messenger();
	mes->init();
	commander com("com1");
	com.setMessenger(mes);

	thread *t0 = nullptr;
	thread *t1 = nullptr;
	t0 = new thread(&commander::data_preparation_thread, com);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	t1 = new thread(&commander::data_processing_thread, com);
	t1->join();
	t0->detach();
}