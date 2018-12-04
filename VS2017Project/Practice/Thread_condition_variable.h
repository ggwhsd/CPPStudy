#pragma once

/*
 * 当一个线程需要依赖于另外一个线程时，可以采用多种选择，比如设置标志位，线程轮训检测标志位，如果为true，则往下执行，否则等待。
 * 但是这种方法，未免过于效率低下，浪费cpu资源。 有人说可以使用sleep，不需要一直检测，这样可以提高cpu使用效率，但是带来一个问题，sleep多久才算是合理。
 * 
 * c++11提供了一个办法，可以采用unique_lock和condition_variable的方法wait和notify_one\notify_all来进行同步。效率都要高于前两者。
 * unique_lock的效率是低于lock_guard的，但是灵活性高。
 * 
 * 同时如下示例，也提供了如何在类中对线程进行创建和处理，可用于面向对象编程。
*/
#include <thread>
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;


class Thread_condition_variable
{

public:
	void data_preparation_thread()
	{
		cout << "preparation\n";
		lock_guard<mutex> lk(mut);
		cout << "lock guard\n";
		this_thread::sleep_for(chrono::milliseconds(5000));
		data_queue.push(1);
		
		data_cond.notify_one();
		cout << "notify\n";
	}

	void data_processing_thread()
	{
		cout << "process begin\n";
		unique_lock<mutex> lk(mut);
		cout << "unique lock\n";
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		cout << "wait\n";
		data_queue.pop();
		lk.unlock();
	}

	void init()
	{
		t0 = new thread(&Thread_condition_variable::data_preparation_thread,this);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		t1 = new thread(&Thread_condition_variable::data_processing_thread, this);
		t1->join();
		t0->detach();

	}
private:
	mutex mut;
	queue<int> data_queue;
	condition_variable data_cond;
	thread *t0;
	thread *t1;
};


void testThread_condition_variable()
{
	Thread_condition_variable tcv;
	tcv.init();
}