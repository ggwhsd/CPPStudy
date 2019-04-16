#pragma once
#include <thread>
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;
#ifdef MATUREAPPROACH_EXPORTS
#define MATUREAPPROACH_API __declspec(dllexport)
#else
#define MATUREAPPROACH_API __declspec(dllimport)
#endif
class IThreadsMessage
{
public:
	virtual string wait() =0;

	virtual void notify(string&& message) =0;
	virtual void notifyAll(string&& message) =0;
	virtual void init()=0;
	virtual void release()=0;
};
extern "C" MATUREAPPROACH_API IThreadsMessage* _stdcall CreateExportObj();
extern "C" MATUREAPPROACH_API void _stdcall DestroyExportObj(IThreadsMessage* pExport);