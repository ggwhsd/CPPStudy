#pragma once
#include "./ThreadsMessageDefine.h"
class ThreadsMessageApi : public IThreadsMessage
{
public:
	virtual string wait();

	virtual void notify(string&& message);
	virtual void notifyAll(string&& message);
	virtual void init();
	virtual void release();
	ThreadsMessageApi();
	~ThreadsMessageApi();
	ThreadsMessageApi(const ThreadsMessageApi& other) = delete;
	ThreadsMessageApi& operator=(const ThreadsMessageApi& other) = delete;

private:
	mutex mut;
	queue<string> data_queue;
	condition_variable data_cond;
};