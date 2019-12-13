#include "./observer.h"
#include <iostream>
#include <algorithm>


ISubject::ISubject()
{
}

ISubject::~ISubject()
{

}

void ISubject::Subscribe(int message, IObserver * observer)
{
		mObservers[message].push_back(observer);
}

void ISubject::UnSubscribe(int message, IObserver * observer)
{
	auto findIt = std::find(mObservers[message].begin(), mObservers[message].end(), observer);
	if(findIt != mObservers[message].end())
		mObservers[message].erase(findIt);
}

class UpdateNotify
{
public:
	void setMessage(int message)
	{
		this->message = message;
	}

	void operator()(IObserver* it)
	{
		it->Update(message);
	}
private:
	int message;
};

void ISubject::Notify(int message)
{
	ObserverList *observers = &mObservers[message];
	//方法1 lambda
	//std::for_each(observers->begin(), observers->end(), [message](IObserver* it) { it->Update(message); });
	//方法2 函数对象
	UpdateNotify un;
	un.setMessage(message);
	std::for_each(observers->begin(), observers->end(), un);
	
}
