#pragma once
/*
	项目中多个线程之间有互相等待执行的依赖关系，但是由于有些线程是用的其他库接口中的功能创建，有些是我们自己开发创建。
	若线程互相依赖，原先的解决办法就是循环等待条件，间隔很短的sleep线程，然后继续检查条件是否满足。这种方式对于资源使用效率不高。
	现在打算使用条件变量，使得这些线程都集中到一起进行通信，将会提高资源使用效率。

	2019-08-14 新增了事件驱动的事件分发中心类，相当于事件总线，但是我不喜欢事件总线这个说法，因为技术专业术语太强。 实际上从应用角度来说，就是事件的信息分发，就如同邮局，物流等，通俗易懂。
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
	char SysId[10];
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





class IEventListener
{
public:
	IEventListener() {};
	virtual ~IEventListener() {};

public:
	virtual bool EventHandle(EVENT1) = 0;
};

/*
  多线程（ 1读 多写 ）消息/事件分发中心，对应于通常意义的事件总线或者事件驱动引擎，应用层面，方便不同模块数据进行通信。
*/
class EventsCenter
{
private:
	static EventsCenter* instance;
	static std::mutex m_mutex;

	string name;
	messenger<EVENT1> * mes;
	bool isOpen; //是否关闭
	thread *td_dispatch;
	mutex m_mutex_update;
	list<IEventListener*> list_listeners;
private :
	EventsCenter(const EventsCenter&) = delete;
	EventsCenter& operator=(const EventsCenter&) = delete;

public:
	static EventsCenter* getInstance()
	{
		if (instance == nullptr)
		{
			std::lock_guard<std::mutex> guard(m_mutex);
			if (instance == nullptr)
				instance = new EventsCenter();
		}
		return instance;
	};
	class GC {
	public:
		~GC()
		{
			
			if (instance != nullptr)
			{
				delete instance;
			}
			
		};
	};
	static EventsCenter::GC gc;
	//注册事件及其监听者,监听者通过receEvent接口方法获取事件类型及其事件内容。
	void addEventListener(IEventListener *listener)
	{
		lock_guard<mutex> lk(m_mutex_update);
		list_listeners.push_back(listener);
	}
	//发送事件
	void sendEvent(EVENT1 ev1)
	{
		/*EVENT1 ev1;
			
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
			}*/
		mes->notify(ev1);
	}
	//事件分发,采用类似广播方式，不进行区分消息类型，由接收者自己判断消息类型来处理
	void eventDispatchLoop()
	{
		while (true)
		{
			EVENT1 result = mes->wait();
			cout << getSystemClock_microSeconds() << __FUNCTION__ << " " << name << endl;
			if (isOpen == false)
			{
				cout << getSystemClock_microSeconds() << __FUNCTION__ << " closed "<<endl;
				break;
			}
			if (result.type != EVENT_TYPE::EVENT_NONE)
			{
				lock_guard<mutex> lk(m_mutex_update);
				bool isContinue=false;
				for(list<IEventListener*>::const_iterator listener = list_listeners.cbegin(); listener!=list_listeners.cend(); listener++)
				{
					isContinue=(*listener)->EventHandle(result);
					if (isContinue == false)
						break;
				}
				
			}
		}
	}
	//运行事件中心。
	void Run()
	{
		
		isOpen = true;
		td_dispatch= new thread(&EventsCenter::eventDispatchLoop, this);
		td_dispatch->detach();
	}
	//关闭事件中心。
	void Close()
	{
		isOpen = false;
		delete td_dispatch;
		td_dispatch = nullptr;
	}
	
	void Init(string str)
	{
		name = str;
		mes = new messenger<EVENT1>();
	}
	EventsCenter()
	{
	
	}
	~EventsCenter()
	{
		delete mes;
	}

	
};

EventsCenter::GC EventsCenter::gc;
EventsCenter* EventsCenter::instance;
mutex EventsCenter::m_mutex;


class TestTickListener : public IEventListener
{
public:
	virtual bool EventHandle(EVENT1 result) override
	{
		if (result.type == EVENT_TYPE::EVENT_TICK)
			cout << getSystemClock_microSeconds() << __FUNCTION__ << " result " << result.type << " " << result.data.tick.name << " " << result.data.tick.volumn << endl;
		return true;
	}
};

class TestOrderListener : public IEventListener
{
public:
	virtual bool EventHandle(EVENT1 result) override
	{
		if (result.type != EVENT_TYPE::EVENT_ORDER)
			return true;

		cout << getSystemClock_microSeconds() << __FUNCTION__ << " result " << result.type << " " << result.data.tick.name << " " << result.data.order.SysId << endl;
		cout << getSystemClock_microSeconds() << __FUNCTION__ << " result " << result.type << " " << result.data.tick.name << " " << result.data.order.SysId << endl;
		return true;
	}
};

#define TEST_SLEEP_SECONDS(timeSpan) std::this_thread::sleep_for(std::chrono::seconds(timeSpan));

void eventsTest()
{
	
	EventsCenter::getInstance()->Init("eventsTest");
	EventsCenter::getInstance()->Run();
	TestTickListener tickListener;
	EventsCenter::getInstance()->addEventListener(&tickListener);
	TestOrderListener *orderListener = new TestOrderListener();
	EventsCenter::getInstance()->addEventListener(orderListener);
	EventsCenter::getInstance()->Run();

	TEST_SLEEP_SECONDS(1);
	EVENT1 ev1;
	
	TICK t;
	strcpy(t.name, "ax1");
	t.price = 1 ;
	t.volumn = 1;

	ev1.type = EVENT_TYPE::EVENT_TICK;
	ev1.data.tick = t;
	EventsCenter::getInstance()->sendEvent(ev1);

	TEST_SLEEP_SECONDS(2);

	ORDER order;
	strcpy(order.name, "or1");
	order.price = 2;
	strcpy(order.SysId,"11111");

	ev1.type = EVENT_TYPE::EVENT_ORDER;
	ev1.data.order = order;
	EventsCenter::getInstance()->sendEvent(ev1);

	TEST_SLEEP_SECONDS(2);
	EventsCenter::getInstance()->Close();

	delete orderListener;

}