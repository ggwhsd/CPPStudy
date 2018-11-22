#pragma once
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
/*
	chrono�������������
	1��durations��һ��ʱ���ȣ�����1�룬һ���ӣ�һСʱ��10����ȵȡ�
	2��Time points�������һ��ʱ�̣�����ĳ�˵����գ��𳵵�վ��ʱ���ȡ�
	3��Clocks��ʱ�ӣ���time point����ʵ������ʱ�ӽ��й������ṩ������ʱ�ӣ�
		a. system_clock ϵͳ����ʱ�ӣ���������һ��Ӧ�ó�����һ����뼶�ĳ�����ȫ���á�������ʹ�û�ȡ��ǰʱ�䣬���ܻ���ֺ�һ�λ�ȡ��ʱ���ǰһ��С�������
		b. steady_clock �ȶ�ʱ�ӣ�ÿ��tick�����Ϊ��С�δ�λ�ɣ������ĵ�����ʱ����һ���ġ��������system_clock���Ǹ����⡣ �ر������ڼ����ʱ��
		c. high_resolution_clock ��߾��ȵ�ʱ�ӣ�ʹ�������tick���ڣ���ʱ����Կ���system_clock����steady_clock��ͬ��ʡ�
*/

using namespace std;
//ʱ�侫��
void testPeriodNum()
{
	cout << "system clock          : ";
	cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << "s" << endl;
	cout << "steady clock          : ";
	cout << chrono::steady_clock::period::num << "/" << chrono::steady_clock::period::den << "s" << endl;
	cout << "high resolution clock : ";
	cout << chrono::high_resolution_clock::period::num << "/" << chrono::high_resolution_clock::period::den << "s" << endl;
	
}

//��
void testSystemClock()
{
	using std::chrono::system_clock;

	//ratio�У���һ���������Եڶ����������������һ��Ƶ�ʣ��˴�Ϊ60*60*24/1����λ�롣
	std::chrono::duration<int, std::ratio<60 * 60 * 24> > one_day(1);

	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;

	std::time_t tt;

	tt = system_clock::to_time_t(today);
	char str[26];
	ctime_s(str, sizeof str, &tt);
	std::cout << "today is: " << str;

	tt = system_clock::to_time_t(tomorrow);
	ctime_s(str, sizeof str, &tt);
	std::cout << "tomorrow will be: " << str;
}

//��
void testSystemClock_second()
{
	using std::chrono::system_clock;

	//milli����ratio<1,1000>�� 1/1000 ��
	std::chrono::duration<int> one_second(1);

	system_clock::time_point timenow = system_clock::now();
	system_clock::time_point timenext = timenow + one_second;

	std::time_t tt;

	tt = system_clock::to_time_t(timenow);
	char str[26];
	ctime_s(str, sizeof str, &tt);
	std::cout << "today is: " << str;

	tt = system_clock::to_time_t(timenext);
	ctime_s(str, sizeof str, &tt);
	std::cout << "tomorrow will be: " << str;
}

//����
void testSystemClock_milliSecond()
{
	using std::chrono::system_clock;

	//milli����ratio<1,1000>�� 1/1000 ��
	std::chrono::duration<int,milli> one_millisecond(1);
	using milli1 = std::chrono::duration<int, milli>;
	
	system_clock::time_point timenow = system_clock::now();
	system_clock::time_point timenext = timenow + one_millisecond;

	cout << "millisecond" << std::chrono::duration_cast< std::chrono::duration<float>>(timenext - timenow).count()<< endl;
}

void testElapsedtime()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::cout << "f(42) = " << '\n';
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout 
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";
	
}