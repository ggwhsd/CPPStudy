#include "stdafx.h"
#include "./ThreadsMessageImpl.h"
#include <iostream>
using namespace std;
string ThreadsMessageApi::wait()
{
	string data("");
	unique_lock<mutex> lk(mut);
	data_cond.wait(lk, [this] {return !data_queue.empty(); });
	if (!data_queue.empty())
	{
		data = data_queue.back();
		data_queue.pop();
	}
	lk.unlock();
	return data;
}
void ThreadsMessageApi::notify(string && message)
{
	lock_guard<mutex> lk(mut);
	data_queue.push(message);
	data_cond.notify_one();
}
void ThreadsMessageApi::notifyAll(string && message)
{
	lock_guard<mutex> lk(mut);
	data_queue.push(message);
	data_cond.notify_all();
}
void ThreadsMessageApi::init()
{

}


void ThreadsMessageApi::release()
{
	delete this;
}

ThreadsMessageApi::ThreadsMessageApi()
{
}

ThreadsMessageApi::~ThreadsMessageApi()
{

}

