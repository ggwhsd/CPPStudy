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


enum EVENT_TYPE
{
	EVENT_NONE,
	EVENT_TICK,
	EVENT_ORDER,
	EVENT_TRADE
};
struct TICK
{
	char name[10];
	double price;
	int volumn;
};

struct ORDER
{
	char name[10];
	double price;
	int volumn;
};

struct TRADE
{
	char name[10];
	double price;
	int volumn;
};

union EVENT_DATA
{
	TRADE trade;
	ORDER order;
	TICK tick;

};

struct EVENT1
{

	EVENT_TYPE type;
	EVENT_DATA data;

};

template<typename T>
class messenger
{

public:
	T wait()
	{
		T data;

		unique_lock<mutex> lk(mut);
		//cout << getSystemClock_microSeconds() << "before wait" << endl;
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		//cout << getSystemClock_microSeconds()<<"after wait" << endl;
		if (!data_queue.empty())
		{
			//cout << getSystemClock_microSeconds() << "get a message :" << (data = data_queue.back()).c_str() << endl;;
			data = data_queue.front();
			data_queue.pop();
		}
		lk.unlock();
		return data;

	}

	void notify(T &message)
	{

		lock_guard<mutex> lk(mut);

		data_queue.push(message);
		//cout << getSystemClock_microSeconds() << "send a message"<< message.c_str() << endl;
		data_cond.notify_one();
		//cout << getSystemClock_microSeconds() << "notify_one" << endl;




	}

	void init()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << getSystemClock_microSeconds() << "init" << endl;

	}
	int  getDepth()
	{
		return data_queue.size();
	}

private:
	mutex mut;
	queue<T> data_queue;
	condition_variable data_cond;

};

class Message
{
private:
	static messenger<EVENT1> * mes;

public:

	static void Set(messenger<EVENT1> * s)
	{
		mes = s;
	}
	static void AddEvent(EVENT1 ev1)
	{
		mes->notify(ev1);
	}
	static EVENT1 GetEvent(EVENT1)
	{
		return mes->wait();
	}
};

void testUnion()
{

	TICK t;
	strcpy(t.name, "ax1");
	t.price = 123;
	t.volumn = 1;

	EVENT1 ev1;
	ev1.type = EVENT_TYPE::EVENT_TICK;
	ev1.data.tick = t;

	queue<EVENT1> q;
	q.push(ev1);
	cout << ev1.type << " " << ev1.data.tick.name << " " << ev1.data.tick.price << " " << ev1.data.tick.volumn << endl;
	EVENT1 &ev2 = q.front();
	q.pop();
	EVENT1 ev3;
	ev3.type = ev2.type;
	ev3.data.tick = ev2.data.tick;

	cout << ev3.type << " " << ev3.data.tick.name << " " << ev3.data.tick.price << " " << ev3.data.tick.volumn << endl;


}


class commander
{
	int index_1 = 0;
	int index_2 = 0;
public:
	void data_preparation_thread()
	{
		while (index_1<10000) {
			index_1 += 1;
			//cout << getSystemClock_microSeconds() << __FUNCTION__ << "begin,"<< index_1 << endl;
			EVENT1 ev1;
			if (index_1 % 2 == 0)
			{
				TICK t;
				strcpy(t.name, "ax1");
				t.price = 1 + index_1;
				t.volumn = index_1;

				ev1.type = EVENT_TYPE::EVENT_TICK;
				ev1.data.tick = t;
			}
			else
			{
				ORDER t;
				strcpy(t.name, "or1");
				t.price = 1 + index_1;
				t.volumn = index_1;

				ev1.type = EVENT_TYPE::EVENT_ORDER;
				ev1.data.order = t;
			}
			mes->notify(ev1);

			//cout << getSystemClock_microSeconds() << __FUNCTION__ << "end" << endl;
		}
		cout << mes->getDepth() << endl;
	}

	void data_processing_thread()
	{
		while (true)
		{
			index_2 += 1;
			//cout << getSystemClock_microSeconds() << __FUNCTION__ << "begin,"<< index_2 << endl;
			EVENT1 result = mes->wait();
			if (result.type != EVENT_TYPE::EVENT_NONE)
			{
				if (result.type == EVENT_TYPE::EVENT_TICK)
					cout << getSystemClock_microSeconds() << __FUNCTION__ << "result " << result.type << " " << result.data.tick.name << " " << result.data.tick.volumn << endl;
				else if (result.type == EVENT_TYPE::EVENT_ORDER)
					cout << getSystemClock_microSeconds() << __FUNCTION__ << "result " << result.type << " " << result.data.tick.name << " " << result.data.order.volumn << endl;
			}
			//cout << getSystemClock_microSeconds() << __FUNCTION__ << "end" << endl;
		}
	}

	void init()
	{




	}

	void setMessenger(messenger<EVENT1> * m)
	{
		mes = m;
	}
	commander(string str)
	{
		name = str;
	}
private:
	string name;
	messenger<EVENT1> * mes;
};

void messengerTest()
{
	messenger<EVENT1> *mes = new messenger<EVENT1>();
	mes->init();
	commander com("com1");
	com.setMessenger(mes);

	thread *t0 = nullptr;
	thread *t1 = nullptr;
	thread *t2 = nullptr;

	t0 = new thread(&commander::data_preparation_thread, com);
	t2 = new thread(&commander::data_preparation_thread, com);

	t0->detach();
	t2->detach();

	t1 = new thread(&commander::data_processing_thread, com);
	t1->join();
	cout << "";
}