#pragma once
#include <thread>
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "CircleVector.h"
using namespace std;
/*
template<typename T>
class BlockingQueue
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
			data = data_queue.pop();
		}
		lk.unlock();
		return data;
	}

	bool notify(T& message)
	{

		lock_guard<mutex> lk(mut);

		bool opRtn=data_queue.push(message);
		//cout << getSystemClock_microSeconds() << "send a message"<< message.c_str() << endl;
		data_cond.notify_one();
		return opRtn;
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
	CicleVector<T> data_queue;
	condition_variable data_cond;

};*/