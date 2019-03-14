#pragma once
#include <iostream>
#include <event.h>
#include <ctime>

#include <thread>

using namespace std;


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
	void addTimer(int seconds, int microseconds, event_callback_fn cb)
	{
		tv_sec = { seconds, microseconds };
		event *timeout = event_new(base, -1, EV_PERSIST | EV_TIMEOUT, cb, NULL);
		event_add(timeout, &tv_sec);
	}
};


void cb(evutil_socket_t fd, short what, void *arg)
{
	cout << "event ocurrence every 1  seconds. " << endl;
}

//////ÒÔÏÂÎª²âÊÔ////////
void threadWork(Timer* timer)
{
	cout << "wait for 3 sencond" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	timer->addTimer(0, 1000000, cb);
}

void TimerTest()
{
	Timer timer;
	thread *t1 = new thread(threadWork,&timer);
	t1->detach();
	timer.SetTimer();
}