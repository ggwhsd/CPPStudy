// GugwHiredisTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "..\GugwHiredis\GugwHiredis.h"
#include <chrono>
using namespace std;



int redisHandler;
char buffer[1024] = { 0 };
int testOne()
{
	redisHandler = Gugw::Gugw_redisConnect("127.0.0.1", 6379);
	if (redisHandler == -1)
	{
		return 0;
	}
	const char *pszRedisPwd = "foobared";

	sprintf_s(buffer, 1024, "AUTH %s", pszRedisPwd);
	Gugw::Gugw_redisReply reply = Gugw::Gugw_redisCommand(redisHandler, buffer);
	std::cout << "结果为:" << reply.replayMsg << std::endl;


	sprintf_s(buffer, "GET %s", "name");
	reply = Gugw::Gugw_redisCommand(redisHandler, buffer);
	std::cout << "结果为:" << reply.replayMsg << std::endl;
}

void testTwo()
{
	
	sprintf_s(buffer, "GET %s", "name");
	Gugw::Gugw_redisReply reply = Gugw::Gugw_redisCommand(redisHandler, buffer);
	
}

typedef chrono::time_point<chrono::steady_clock, chrono::milliseconds> milliClock_type;
int main()
{
	testOne();
	int iMax = 1000 * 1000;
	milliClock_type temp_now = chrono::time_point_cast<chrono::milliseconds>(chrono::steady_clock::now());
	int i = 0;
	while (i < iMax)
	{
		i++;
		testTwo();
	}
	milliClock_type temp_now2 = chrono::time_point_cast<chrono::milliseconds>(chrono::steady_clock::now());
	double secDur = (temp_now2 - temp_now).count() / 1000.0;
	cout << "耗时 "<< secDur  << "秒" << endl;
	cout << "吞吐量 " <<  iMax / secDur << " 次/秒" << endl;
    std::cout << "Hello World!\n";
	cin >> i;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
