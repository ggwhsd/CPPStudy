// StudyBase.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "./InterfaceDefineAndRealize.h"
#include <iostream>
#include "a.h"
//#include "./b.h"
#include "./ThreadsMessageDefine.h"
//#pragma comment(lib, "../Debug/GUGWAPI.lib")
//#pragma comment(lib, "../Debug/OTHERAPI.lib")
#pragma comment(lib, "../Release/ThreadsMessengerApi.lib")

void testThread(IThreadsMessage *pThreadM)
{
	string str = pThreadM->wait();
	cout << std::this_thread::get_id()<<" receive "<< str << endl;
}


int main()
{

	//CNaiveApproach obj(10);
	//obj.Test();
	//obj.Func();
	//IExport项目的导出方式更好些，因为这样只要导出接口，而不需要到处每个类以及基类。
	/*IExport* pExport = CreateExportObj();
	pExport->Hi();
	pExport->Test();
	DestroyExportObj(pExport);
	*/
	system("pause");
	cout << std::this_thread::get_id() << endl;
	IThreadsMessage *pThreadM = CreateExportObj();
	thread  t1(testThread, pThreadM);
	t1.detach();
	this_thread::sleep_for(std::chrono::milliseconds(10000));
	pThreadM->notify("I tell you");
	system("pause");
    return 0;
}

