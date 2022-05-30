#pragma once
#include <iostream>
#include <event.h>
#include <ctime>

#include <thread>

using namespace std;

struct dataTest
{
	event* field1;
	int field2;
};

void empytCB(evutil_socket_t fd, short what, void *arg)
{
}

class Timer
{
private:
	timeval tv_sec;
	event_base *base;

public:
	void SetTimer()
	{
		tv_sec = { 1, 0 };
		base = event_base_new();
		event *timeout = event_new(base, -1, EV_PERSIST | EV_TIMEOUT, empytCB, NULL);
		event_add(timeout, &tv_sec);
		event_base_dispatch(base);
		cout << "dispatch" << endl;
	}
public:
	void addTimer(int seconds, int microseconds, event_callback_fn cb,dataTest* dt)
	{
		tv_sec = { seconds, microseconds };
		event *timeout = event_new(base, -1, EV_PERSIST | EV_TIMEOUT, cb, dt);
		dt->field1 = timeout;
		event_add(timeout, &tv_sec);
	}

	void addOnceTimer(int seconds, int microseconds, event_callback_fn cb, dataTest* dt)
	{
		tv_sec = { seconds, microseconds };
		event* timeout = event_new(base, -1,  EV_TIMEOUT, cb, dt);
		dt->field1 = timeout;
		event_add(timeout, &tv_sec);
	}
};

//传入数据类型
void cb(evutil_socket_t fd, short what, void *arg)
{
	dataTest *dt = (dataTest*)arg;
	dt->field2--;
	
	cout << getSystemClock_microSeconds()<<"event ocurrence every 10ms"  << "  seconds.  dataTest:" <<  dt->field2 << endl;
	if (dt->field2 < 0)
	{
		event_del(dt->field1);
	}
	
}

//////以下为测试////////

dataTest dt{ nullptr, 3 };
void threadWork(Timer* timer)
{
	
	
	cout << "wait for 3 sencond" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	cout << getSystemClock_microSeconds() << "add timer:" << endl;
		timer->addTimer(0, 1000*1000, cb, &dt);

	dt.field2 = 10;

	
}

void TimerTest()
{
	Timer timer;
	thread *t1 = new thread(threadWork,&timer);
	t1->detach();
	timer.SetTimer();
}