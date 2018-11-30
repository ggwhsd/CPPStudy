#pragma once
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <iomanip>
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

	typedef chrono::time_point<chrono::system_clock, chrono::milliseconds> microClock_type;
	microClock_type tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
	
	//ת��Ϊctime.���ڴ�ӡ��ʾʱ��   
	time_t tt = chrono::system_clock::to_time_t(tp);
	char _time[50];
	ctime_s(_time, sizeof(_time), &tt);
	cout << "now time is : " << _time<< ":"<<tp.time_since_epoch().count() % (1000) << "ms\n";
	//�������1970-1-1,00:00��ʱ�䳤�ȣ���Ϊ��ǰʱ��㶨��ľ���Ϊ���룬����������Ǻ���   
	cout << "" << endl;

	tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
	tt = chrono::system_clock::to_time_t(tp);
	char timebuf[50];
	tm ltm;
	localtime_s(&ltm,&tt);
	strftime(timebuf, 30, "%F %R:%S", &ltm);
	cout <<  timebuf << ":"<< tp.time_since_epoch().count() % (1000) << "ms\n";
	int i = 0;
	while (i < 10000)
	{
		
		i++;
	}
	microClock_type tp2 = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
	//ת��Ϊctime.���ڴ�ӡ��ʾʱ��   
	 tt = chrono::system_clock::to_time_t(tp2);
	localtime_s(&ltm, &tt);
	strftime(timebuf, 30, "%F %R:%S", &ltm);
	cout << " " << timebuf << ":" << tp2.time_since_epoch().count() % (1000) << "ms\n";
	
}

void testElapsedtime()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	int i = 0;
	
	while (i < 100000)
	{
		
		i++;
	}
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	
	std::cout 
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";
	
}


void testSystemClock_microSeconds()
{
	using std::chrono::system_clock;

	//milli����ratio<1,1000>�� 1/1000 ��
	//mirco����ratio<1,1000000>�� 1/1000000 ��
	std::chrono::duration<int, std::micro> one_mircoSecond(1);
	using micro1 = std::chrono::duration<int, micro>;

	system_clock::time_point timenow = system_clock::now();
	system_clock::time_point timenext = timenow + one_mircoSecond;
	//count�ĵ�λ����
	cout << "one_mircoSecond" << std::chrono::duration_cast< std::chrono::duration<float>>(timenext - timenow).count() << endl;


	//����time_point��ʱ�Ӻ�count��С����Ϊ΢�룬Ŀǰʹ�õ�windows����countĬ����0.1΢�롣
	typedef chrono::time_point<chrono::system_clock, chrono::microseconds> microClock_type;
	time_t tt;
	//��system_clock��time_point�ṹת��Ϊ΢�����
	microClock_type tp = chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now());
	int i = 0;
	while (i < 100000)
	{

		i++;
	}
	microClock_type tp2 = chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now());
	tt = chrono::system_clock::to_time_t(tp);
	char timebuf[50];
	tm ltm;
	localtime_s(&ltm, &tt);
	strftime(timebuf, 30, "%F %R:%S", &ltm);
	//count�ĵ�λ��΢�룬��ʾΪ����Ҫ����10��-6�η�
	cout << timebuf << ":" << setfill('0') << setw(6)<<tp.time_since_epoch().count() % (1000000) << "micros\n";
	//ת��Ϊctime.���ڴ�ӡ��ʾʱ��   
	tt = chrono::system_clock::to_time_t(tp2);
	localtime_s(&ltm, &tt);
	strftime(timebuf, 30, "%F %R:%S", &ltm);
	cout << " " << timebuf << ":" <<  setfill('0') << setw(6) <<tp2.time_since_epoch().count() % (1000000) << "micros\n";
	
	
	
	char mircostr[8];
	mircostr[7] = '\0';
	sprintf_s(mircostr,".%06d", (int)(tp2.time_since_epoch().count() % (1000000)));
	cout << mircostr << endl;
	string str(timebuf);
	
	str.append(mircostr);
	cout << "str=" << str.c_str() << endl;

	strcat_s(timebuf, mircostr);
	cout << "timebuf=" << timebuf << endl;

}
typedef chrono::time_point<chrono::system_clock, chrono::microseconds> microClock_type;
string getSystemClock_microSeconds()
{
	
	microClock_type tp2 = chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now());
	time_t tt;
	tt = chrono::system_clock::to_time_t(tp2);
	char timebuf[50];
	tm ltm;
	localtime_s(&ltm, &tt);
	strftime(timebuf, 30, "%F %R:%S", &ltm);
	char mircostr[8];
	mircostr[7] = '\0';
	sprintf_s(mircostr, ".%06d", (int)(tp2.time_since_epoch().count() % (1000000)));
	string str(timebuf);
	str.append(mircostr);
	return str;
}