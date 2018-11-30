#pragma once
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <iomanip>
/*
	chrono里面有三个概念：
	1、durations：一个时间跨度，例如1秒，一分钟，一小时，10毫秒等等。
	2、Time points：具体的一个时刻，例如某人的生日，火车到站的时间点等。
	3、Clocks：时钟，将time point和真实的物理时钟进行关联。提供了三种时钟：
		a. system_clock 系统日历时钟，可以满足一般应用场景，一般毫秒级的场景完全可用。若连续使用获取当前时间，可能会出现后一次获取的时间比前一次小的情况。
		b. steady_clock 稳定时钟，每个tick（理解为最小滴答单位吧）所消耗的物理时间是一样的。不会出现system_clock的那个问题。 特别适用于计算耗时。
		c. high_resolution_clock 最高精度的时钟，使用了最短tick周期，有时候可以看成system_clock或者steady_clock的同义词。
*/

using namespace std;
//时间精度
void testPeriodNum()
{
	cout << "system clock          : ";
	cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << "s" << endl;
	cout << "steady clock          : ";
	cout << chrono::steady_clock::period::num << "/" << chrono::steady_clock::period::den << "s" << endl;
	cout << "high resolution clock : ";
	cout << chrono::high_resolution_clock::period::num << "/" << chrono::high_resolution_clock::period::den << "s" << endl;
	
}

//天
void testSystemClock()
{
	using std::chrono::system_clock;

	//ratio中，第一个参数除以第二个参数，结果就是一个频率，此处为60*60*24/1，单位秒。
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

//秒
void testSystemClock_second()
{
	using std::chrono::system_clock;

	//milli等于ratio<1,1000>即 1/1000 秒
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

//毫秒
void testSystemClock_milliSecond()
{
	using std::chrono::system_clock;

	//milli等于ratio<1,1000>即 1/1000 秒
	std::chrono::duration<int,milli> one_millisecond(1);
	using milli1 = std::chrono::duration<int, milli>;
	
	system_clock::time_point timenow = system_clock::now();
	system_clock::time_point timenext = timenow + one_millisecond;

	cout << "millisecond" << std::chrono::duration_cast< std::chrono::duration<float>>(timenext - timenow).count()<< endl;

	typedef chrono::time_point<chrono::system_clock, chrono::milliseconds> microClock_type;
	microClock_type tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
	
	//转换为ctime.用于打印显示时间   
	time_t tt = chrono::system_clock::to_time_t(tp);
	char _time[50];
	ctime_s(_time, sizeof(_time), &tt);
	cout << "now time is : " << _time<< ":"<<tp.time_since_epoch().count() % (1000) << "ms\n";
	//计算距离1970-1-1,00:00的时间长度，因为当前时间点定义的精度为毫秒，所以输出的是毫秒   
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
	//转换为ctime.用于打印显示时间   
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

	//milli等于ratio<1,1000>即 1/1000 秒
	//mirco等于ratio<1,1000000>即 1/1000000 秒
	std::chrono::duration<int, std::micro> one_mircoSecond(1);
	using micro1 = std::chrono::duration<int, micro>;

	system_clock::time_point timenow = system_clock::now();
	system_clock::time_point timenext = timenow + one_mircoSecond;
	//count的单位是秒
	cout << "one_mircoSecond" << std::chrono::duration_cast< std::chrono::duration<float>>(timenext - timenow).count() << endl;


	//设置time_point的时钟和count最小周期为微秒，目前使用的windows机器count默认是0.1微秒。
	typedef chrono::time_point<chrono::system_clock, chrono::microseconds> microClock_type;
	time_t tt;
	//将system_clock的time_point结构转换为微秒计算
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
	//count的单位是微秒，显示为秒需要乘以10的-6次方
	cout << timebuf << ":" << setfill('0') << setw(6)<<tp.time_since_epoch().count() % (1000000) << "micros\n";
	//转换为ctime.用于打印显示时间   
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