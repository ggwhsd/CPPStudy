#pragma once
#include <map>
#include <vector>
#include <iostream>
class IObserver
{
public:
	virtual ~IObserver() {}
	virtual void Update(int message) = 0; //pure virtual 用于接口的。
};

class ISubject
{
public:
	ISubject();
	virtual ~ISubject();
	virtual void Subscribe(int message, IObserver *observer);
	virtual void UnSubscribe(int message, IObserver *observer);
	virtual void Notify(int);
private:
	typedef std::vector<IObserver*> ObserverList;
	typedef std::map<int, ObserverList> ObserverMap;
	ObserverMap mObservers;

};

class MySubject :public ISubject
{
public:
	enum Messages { ADD, REMOVE };

};

class MyObserver : public IObserver
{
public:
	explicit MyObserver(const std::string &str) :mName(str) {}
	void Update(int message)
	{
		std::cout << mName.c_str() << " Receive message";
		std::cout << message << std::endl;
	}
private:
	std::string mName;
};
