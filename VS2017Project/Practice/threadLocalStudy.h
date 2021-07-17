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
		thread_local int count = 0;    //count�Ǹ���ʱ��������������thread_local��������������ÿ���߳��ж���һֱ����һ���ڴ�ռ䣬��һ�ε�����������������ᴴ����
		count++;
		cout << name << "��count=" << count << endl;
	}
};



void testThreadLocal()
{
	numTest n1;
	//������������ĳЩ���̰߳�ȫ�������ϣ��Ҿ��û�ȽϺã�����ÿ���߳�ֻ����һ������������ÿִ��һ�ξʹ���һ�Ρ�
	std::thread([&](string name) { n1.test(name);  n1.test(name);  }, "thread1").join();
	std::thread([&](string name) { n1.test(name); n1.test(name); }, "thread2").join();

}