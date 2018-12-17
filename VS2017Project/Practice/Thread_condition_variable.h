#pragma once

/*
 * 当一个线程需要依赖于另外一个线程时，可以采用多种选择，比如设置标志位，线程轮训检测标志位，如果为true，则往下执行，否则等待。
 * 但是这种方法，未免过于效率低下，浪费cpu资源。 有人说可以使用sleep，不需要一直检测，这样可以提高cpu使用效率，但是带来一个问题，sleep多久才算是合理。
 * 
 * c++11提供了一个办法，可以采用unique_lock和condition_variable的方法wait和notify_one\notify_all来进行同步。效率都要高于前两者。
 * unique_lock的效率是低于lock_guard的，但是灵活性高。
 * 
 * 同时如下示例，也提供了如何在类中对线程进行创建和处理，可用于面向对象编程。
 * 
 * 性能对比：testThread_condition_variable() 对比使用notify与mutex检测之间的时间延迟，在windows上基本上没有什么差距。
*/
#include <thread>
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "./chronoStudy.h"
using namespace std;

string testResult;
struct timeConsume {
	long send_time;
	long receive_time;
	long diff()
	{
		return receive_time - send_time;
	}
};

long avg1 = 0;
long avg2 = 0;
long avg3 = 0;

class Thread_condition_variable
{

public:
	void data_preparation_thread()
	{
		
		this_thread::sleep_for(chrono::milliseconds(500));
		
		lock_guard<mutex> lk(mut);
		data_queue.push(1);
		tt.send_time = getMicroSeconds();
		data_cond.notify_one();
		
		
		
	}

	void data_processing_thread()
	{
		unique_lock<mutex> lk(mut);
		
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		tt.receive_time = getMicroSeconds();
		data_queue.pop();
		lk.unlock();
	}

	void init()
	{
		tt.receive_time = 0;
		tt.send_time = 0;
		t0 = new thread(&Thread_condition_variable::data_preparation_thread,this);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		t1 = new thread(&Thread_condition_variable::data_processing_thread, this);
		t1->join();
		t0->detach();
	
		cout << "用notify_one来进行线程同步: 耗时微秒 = [" << tt.diff() << "]" << endl;
		avg1 = (avg1 + tt.diff());

	}
private:
	mutex mut;
	queue<int> data_queue;
	condition_variable data_cond;
	thread *t0;
	thread *t1;
	timeConsume tt;
};



class Thread_LockGuardmutex
{

public:
	void data_preparation_thread()
	{
		
		lock_guard<mutex> lk(mut);
		this_thread::sleep_for(chrono::milliseconds(500));
		data_queue.push(1);
		tt.send_time = getMicroSeconds();
		
	}

	void data_processing_thread()
	{
		
		lock_guard<mutex> lk(mut);
		tt.receive_time = getMicroSeconds();
		data_queue.pop();
	}

	void init()
	{
		tt.receive_time = 0;
		tt.send_time = 0;
		t0 = new thread(&Thread_LockGuardmutex::data_preparation_thread, this);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		t1 = new thread(&Thread_LockGuardmutex::data_processing_thread, this);
		t1->join();
		t0->detach();
		cout <<"用lock guard<mutex>进行线程同步: 耗时微秒 = ["<< tt.diff() <<"]" << endl;
		avg2 = (avg2 + tt.diff());

	}
private:
	mutex mut;
	queue<int> data_queue;
	condition_variable data_cond;
	thread *t0;
	thread *t1;
	timeConsume tt;
};


class Thread_mutex
{

public:
	void data_preparation_thread()
	{

		mut.lock();
		this_thread::sleep_for(chrono::milliseconds(500));
		data_queue.push(1);
		tt.send_time = getMicroSeconds();
		mut.unlock();
		

	}

	void data_processing_thread()
	{

		mut.lock();
		tt.receive_time = getMicroSeconds();
		data_queue.pop();
		mut.unlock();
	}

	void init()
	{
		tt.receive_time = 0;
		tt.send_time = 0;
		t0 = new thread(&Thread_mutex::data_preparation_thread, this);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		t1 = new thread(&Thread_mutex::data_processing_thread, this);
		t1->join();
		t0->detach();
		cout << "用mutex.lock进行线程同步: 耗时微秒 = [" << tt.diff() << "]" << endl;
		avg3 = (avg3 + tt.diff());

	}
private:
	mutex mut;
	queue<int> data_queue;
	condition_variable data_cond;
	thread *t0;
	thread *t1;
	timeConsume tt;
};


void testAvgResult(int i)
{
	cout << "平均耗时:" << endl;
	cout << avg1 / i << endl;
	cout << avg2 / i << endl;
	cout << avg3 / i << endl;
}


void testThread_condition_variable()
{

	int i = 0; while (i < 60) { 
	cout << "------------------------------------------" << i << "---------------------" << endl; Thread_condition_variable tcv;
	tcv.init();
	Thread_LockGuardmutex tlgm;
	tlgm.init();
	Thread_mutex tm;
	tm.init(); i++; }
	testAvgResult(i);
	
}
