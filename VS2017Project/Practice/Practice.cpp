// Practice.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "./libevent_EvbufferStudy.h"
//#include "libeventHello.h"
#include "chronoStudy.h"
#include "WindowsFileApi.h"
#include "exceptionStudy.h"
#include "./NetBigEndStudy.h"
#include "JSONStudy.h"
#include "./Thread_condition_variable.h"
#include "./shardPtrStudy.h"
#include "./libEventProxy.h"
#include "./STLMap.h"
#include "./STLVector.h"
#include "./streamStudy.h"
#include "./logger.h"
#include "./xmlStudy.h"
#include "./Cpp11_Function_Study.h"
#include "./ThreadPoolsStudy.h"
#include "./ThreadsWaitNotifyManager.h"
#include "./coutStudy.h"
using namespace std;


int main()
{
	//testSystemClock();
	//testPeriodNum();
	//testSystemClock_second();
	//testSystemClock_milliSecond();
	//testSystemClock_microSeconds();
	//testElapsedtime();
	//testLibeventHello(0, nullptr); 
	//testCreateDirectory();
	//testShowExecDirectory();
	//testTryException();
	//testLibeventEvbuffer(0, nullptr);
	//testBigEnd();
	//testJsonRead();
	/*testThread_condition_variable();
	*/
	//testSharedPtr();
	//testAutoPtr();

	
	/*ServerLib server;
	server.startByNewThread();
	ClientLib client;
	client.SocketStart();*/

	/*
	cout << "choice server or client:\n1:server \n2:client)\n";
	int choice = 0;
	cin >> choice;
	cin.get();
	ServerLib server;
	ClientLib client;
	if (choice == 1) {
		
		server.startByNewThread();
		cin.get();
	}
	else {
		
		client.LibEventStart();
		cin.get();
	}
	*/


	//STLMapTest map;
	//map.baseFuctionTest();

	/*STLVectorTest vectorTest;
	vectorTest.testVectorErase(13);
	*/

	//JSONSTUDY::stringSerialized();
	//JSONSTUDY::JsonCreateMethod1();
	//JSONSTUDY::JsonCreateMethod2();

	
	//ostreamTest();

	
/*	GGWlogger mylogger("testfile");
	mylogger.SetLevel(LOGLEVEL::LOG_DEBUG);
	mylogger.WriteLog( "hhhhhhh", LOGLEVEL::LOG_INFO);
	mylogger.WriteLog("hhhhhhh");
	*/

	//xmlRead();
	//FunctionTest();
	//doubleReferenceTest();

	//testThread_condition();



/*
	// create thread pool with 4 worker threads
	ThreadPool pool(4);
	// enqueue and store future
	auto result = pool.enqueue([](int answer) { return answer; }, 42);
	// get result from future
	std::cout << result.get() << std::endl;
*/

	//messengerTest();

	//ostreamTest();

	/*
	int BidVolumn = 1;
	int AskVolumn = 1;
	double AskPrice = 286.15;  
	double BidPrice = 286.05;
	int marketSpread = 6;
	double tickPrice = 0.05;
	if (BidVolumn>0 && AskVolumn>0 )
	{
		cout << "1 true";
	}
	if ((AskPrice - BidPrice >= (2-0.1) * tickPrice))     //0.099999999999965894 >= 0.10000000000000001
		cout << "2 true";
	if ((AskPrice - BidPrice <= (marketSpread+0.1) * tickPrice))
		cout << " 3 true";
	if ((AskPrice - BidPrice - 2 * tickPrice)>=-0.001*tickPrice)
		cout << "4 true";
	if (fabs(AskPrice - BidPrice - 2 * tickPrice) < 0.1*tickPrice)
		cout << "5 true";
	
	if ((AskPrice - BidPrice-2*tickPrice) >= -0.1 * tickPrice)     //0.099999999999965894 >= 0.10000000000000001
		cout << "2 true";

	BidPrice = 0.0;
	if (BidPrice == 0)
		cout << "6 true";
		*/
   
		
	//messengerTest();

  // testElapsedmilliTime();
	testCout();
	cin.get();
	cout << "end" << endl;
	cin.get();
    return 0;
}

