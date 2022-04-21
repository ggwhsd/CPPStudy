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
		//整体执行结果 atomic的性能是mutex的三倍，但是这只是当前这个临界区只有一行代码的情况下，也就是说临界区计算量很小。如果临界区计算量大，我觉得使用mutex和atomic相差微乎其微。
		//所以，我认为两者使用的选择并非两个关键字的性能，而是场景，atomic在当前场景下，使得代码很干净，也不存在死锁等可能性，
		//同时atomic用于CAS编程思想，该思想可以理解是一种乐观锁的性质，而mutex则是一种悲观锁的实现。
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

atomic_flag winner = ATOMIC_FLAG_INIT;  //将结构体atomic_flag赋值为 {0}  ,默认false，clear之后未false，set为true

void Count1million(int id)
{
	while (!ready) 
	{ 
		//yield属于出让cpu的时间片，属于一种hint方式，下一个时间片可能还会是当前线程运行。
		std::this_thread::yield(); 
	}
	//此处 volatile 表示每次用i时，都要从i的内存地址读取，而不是编译器优化之后的读取方式。此处我觉得并无多大效果，可能是为了延长运行时间吧。
	for (volatile int i = 0; i < 1000000; ++i) 
	{}         
	if (!winner.test_and_set())   // 读取winner当前值并返回，然后设置winner为true。 该过程是一个原子操作。  所以，只有一行代码会读取到false，之后其他线程读取该winner都是返回true。
	{ 
		std::cout << "thread #" << id << " is winner !\n"; 
	}
}

//可以看出atomic_flag使用场景和mutex直观比起来，还是mutex更易用。 
void TestAtomicFlag()
{
	std::vector<std::thread> threads;
	std::cout << "运行 10 线程 ，看看谁先计算到100万 \n";
	for (int i = 1; i <= 10; ++i) 
		threads.push_back(std::thread(Count1million, i));
	ready = true;
	for (auto& th : threads) 
		th.join();

	
}