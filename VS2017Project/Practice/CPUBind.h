#pragma once


#include <windows.h>   
#include <string> 
#include <thread>
#include <iostream>
using namespace std;
struct Ddata
{
	int a[100];
	char b[1204];

};
void running(int seconds) {
	//Sleep(seconds * 1000);

	Ddata d;
	int i = 1;
	long long result = 0;
	int b = 0;
	while (i < seconds)
	{
		result = sqrt(i)*pow(i, 2);
		int j = 0;
		while (j < 100)
		{
			int s = sqrt(j);
			if (s % 999 == 3)
				b = s;
			j++;
		}
		d.a[0] = b;
		d.b[0] = i & 0x000000ff;
		i++;
	}

	std::cout << "sleep for " << seconds << "(s)" << std::endl;
}
void running1()
{

	std::cout << "当前线程:" << std::this_thread::get_id() << std::endl;
	SetThreadAffinityMask(GetCurrentThread(), 0x08);
	running(99999999);
}
void TestBindCPU()
{
	//HANDLE handle = GetCurrentThread();
	std::cout << "当前线程:" << std::this_thread::get_id() << std::endl;

	thread s1(running1);
	/*
	  0x01 cpu0
	  0x02 cpu1
	  0x03 cpu0 cpu1
	  0x04 cpu2
	  0x05 cpu0 cpu2
	  0x06 cpu1 cpu2
	  0x07 cpu0 1 2
	  0x08 cpu3
	*/
	SetThreadAffinityMask(GetCurrentThread(), 0x07);
	LARGE_INTEGER start, end;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq); //windows自带的高性能时间，实际上我感觉Chrono库中差不多
	QueryPerformanceCounter(&start);


	running(99999999);
	QueryPerformanceCounter(&end);
	std::cout << "start.QuadPart = " << start.QuadPart << std::endl;
	std::cout << "end.QuadPart = " << end.QuadPart << std::endl;
	std::cout << "consume value = " << (end.QuadPart - start.QuadPart) << std::endl;
	std::cout << " time consumed = " << (end.QuadPart - start.QuadPart) / (double)freq.QuadPart << "(s)" << std::endl;  //output consumed time  

}