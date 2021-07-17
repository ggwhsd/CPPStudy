#pragma once
#include <thread>
#include <iostream>
#include <string>
using namespace std;

class numTest {
public:
	numTest() {}
	~numTest() {}
	void test(const string& name)
	{
		thread_local int count = 0;    //count是个临时变量，但是由于thread_local声明，所以其在每个线程中都会一直存在一个内存空间，下一次调用这个函数，将不会创建。
		count++;
		cout << name << "的count=" << count << endl;
	}
};



void testThreadLocal()
{
	numTest n1;
	//这种特性用在某些非线程安全工具类上，我觉得会比较好，这样每个线程只创建一个副本，不用每执行一次就创建一次。
	std::thread([&](string name) { n1.test(name);  n1.test(name);  }, "thread1").join();
	std::thread([&](string name) { n1.test(name); n1.test(name); }, "thread2").join();

}