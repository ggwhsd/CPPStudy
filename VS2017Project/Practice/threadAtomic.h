#pragma once


#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>
#include "./chronoStudy.h"
using namespace std;


class Thread_atomic_int
{
public:
	int i;
	Thread_atomic_int():i(10000000)
	{
		count = 0;
	}
	void Inc()
	{
		int j = 0;
		while (j < i)
		{
		
			count++;
		
			j++;
		}
	}
	void Start()
	{
		long startTime = getMicroSeconds();
		t0 = new thread(&Thread_atomic_int::Inc, this);
		t1 = new thread(&Thread_atomic_int::Inc, this);
		t0->join();
		t1->join();
		long stopTime = getMicroSeconds();
		cout << "Thread_atomic_int\tcount="<<count <<"\ttime="<< stopTime-startTime << endl;
	}
private:
	atomic<int> count;
	
	thread *t0;
	thread *t1;

};

class Thread_mutex_int
{
public:
	int i;
	Thread_mutex_int() :i(10000000)
	{
		count = 0;
	}
	void Inc()
	{
		int j = 0;
		while (j < i)
		{
			mlock.lock();
			count++;
			mlock.unlock();
			j++;
		}
	}
	void Start()
	{
		long startTime = getMicroSeconds();
		t0 = new thread(&Thread_mutex_int::Inc, this);
		t1 = new thread(&Thread_mutex_int::Inc, this);
		t0->join();
		t1->join();
		long stopTime = getMicroSeconds();
		cout << "Thread_mutex_int\tcount=" << count << "\ttime=" << stopTime - startTime << endl;
	}
private:
	int count;
	mutex mlock;
	thread *t0;
	thread *t1;
};




void TestAtomic()
{
	int testCount = 10;
	while (testCount > 0)
	{
		//����ִ�н�� atomic��������mutex��������������ֻ�ǵ�ǰ����ٽ���ֻ��һ�д��������£�Ҳ����˵�ٽ�����������С������ٽ������������Ҿ���ʹ��mutex��atomic���΢����΢��
		//���ԣ�����Ϊ����ʹ�õ�ѡ�񲢷������ؼ��ֵ����ܣ����ǳ�����atomic�ڵ�ǰ�����£�ʹ�ô���ܸɾ���Ҳ�����������ȿ����ԣ�
		//ͬʱatomic����CAS���˼�룬��˼����������һ���ֹ��������ʣ���mutex����һ�ֱ�������ʵ�֡�
		Thread_atomic_int t1;
		t1.Start();
		Thread_mutex_int t2;
		t2.Start();
		testCount--;
	}
}




class AtomicClassOne
{
public:
	AtomicClassOne()
	{
		value = 0;
	}
	int value;
};



atomic<bool> ready(false);

atomic_flag winner = ATOMIC_FLAG_INIT;  //���ṹ��atomic_flag��ֵΪ {0}  ,Ĭ��false��clear֮��δfalse��setΪtrue

void Count1million(int id)
{
	while (!ready) 
	{ 
		//yield���ڳ���cpu��ʱ��Ƭ������һ��hint��ʽ����һ��ʱ��Ƭ���ܻ����ǵ�ǰ�߳����С�
		std::this_thread::yield(); 
	}
	//�˴� volatile ��ʾÿ����iʱ����Ҫ��i���ڴ��ַ��ȡ�������Ǳ������Ż�֮��Ķ�ȡ��ʽ���˴��Ҿ��ò��޶��Ч����������Ϊ���ӳ�����ʱ��ɡ�
	for (volatile int i = 0; i < 1000000; ++i) 
	{}         
	if (!winner.test_and_set())   // ��ȡwinner��ǰֵ�����أ�Ȼ������winnerΪtrue�� �ù�����һ��ԭ�Ӳ�����  ���ԣ�ֻ��һ�д�����ȡ��false��֮�������̶߳�ȡ��winner���Ƿ���true��
	{ 
		std::cout << "thread #" << id << " is winner !\n"; 
	}
}

//���Կ���atomic_flagʹ�ó�����mutexֱ�۱�����������mutex�����á� 
void TestAtomicFlag()
{
	std::vector<std::thread> threads;
	std::cout << "���� 10 �߳� ������˭�ȼ��㵽100�� \n";
	for (int i = 1; i <= 10; ++i) 
		threads.push_back(std::thread(Count1million, i));
	ready = true;
	for (auto& th : threads) 
		th.join();

	
}