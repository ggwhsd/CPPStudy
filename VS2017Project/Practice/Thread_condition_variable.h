#pragma once

/*
 * ��һ���߳���Ҫ����������һ���߳�ʱ�����Բ��ö���ѡ�񣬱������ñ�־λ���߳���ѵ����־λ�����Ϊtrue��������ִ�У�����ȴ���
 * �������ַ�����δ�����Ч�ʵ��£��˷�cpu��Դ�� ����˵����ʹ��sleep������Ҫһֱ��⣬�����������cpuʹ��Ч�ʣ����Ǵ���һ�����⣬sleep��ò����Ǻ���
 * 
 * c++11�ṩ��һ���취�����Բ���unique_lock��condition_variable�ķ���wait��notify_one\notify_all������ͬ����Ч�ʶ�Ҫ����ǰ���ߡ�
 * unique_lock��Ч���ǵ���lock_guard�ģ���������Ըߡ�
 * 
 * ͬʱ����ʾ����Ҳ�ṩ����������ж��߳̽��д����ʹ�����������������̡�
 * 
 * ���ܶԱȣ�testThread_condition_variable() �Ա�ʹ��notify��mutex���֮���ʱ���ӳ٣���windows�ϻ�����û��ʲô��ࡣ
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
	
		cout << "��notify_one�������߳�ͬ��: ��ʱ΢�� = [" << tt.diff() << "]" << endl;
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
		cout <<"��lock guard<mutex>�����߳�ͬ��: ��ʱ΢�� = ["<< tt.diff() <<"]" << endl;
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
		cout << "��mutex.lock�����߳�ͬ��: ��ʱ΢�� = [" << tt.diff() << "]" << endl;
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
	cout << "ƽ����ʱ:" << endl;
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
