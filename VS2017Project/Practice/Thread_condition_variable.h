#pragma once

/*
 * ��һ���߳���Ҫ����������һ���߳�ʱ�����Բ��ö���ѡ�񣬱������ñ�־λ���߳���ѵ����־λ�����Ϊtrue��������ִ�У�����ȴ���
 * �������ַ�����δ�����Ч�ʵ��£��˷�cpu��Դ�� ����˵����ʹ��sleep������Ҫһֱ��⣬�����������cpuʹ��Ч�ʣ����Ǵ���һ�����⣬sleep��ò����Ǻ���
 * 
 * c++11�ṩ��һ���취�����Բ���unique_lock��condition_variable�ķ���wait��notify_one\notify_all������ͬ����Ч�ʶ�Ҫ����ǰ���ߡ�
 * unique_lock��Ч���ǵ���lock_guard�ģ���������Ըߡ�
 * 
 * ͬʱ����ʾ����Ҳ�ṩ����������ж��߳̽��д����ʹ�����������������̡�
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