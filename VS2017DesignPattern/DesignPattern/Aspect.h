#pragma once
#include <iostream>
#include <string>
#include <mutex>
using namespace std;
/*
网上看到的一种方法，利用构造和析构机制，来实现C++中的AOP。
另外，通过代理设计模式也可以实现AOP，只是不够通用。
*/
template <class T>
class Aspect
{
private:
	T* m_pAction;
protected:
	Aspect(T* pAction) :m_pAction(pAction)
	{}
	//因为是protected析构函数，所以无法创建栈对象。
	virtual ~Aspect()
	{
	}
public:
	//重载指针操作符
	T * operator->()
	{
		return m_pAction;
	}
};

//模拟一个日志切面
template <class T>
class LogAspect: public Aspect<T>
{
private:
	const string m_logName;

public:
	LogAspect(T* pAction, string name = "") : Aspect<T>(pAction), m_logName(name)
	{
		std::cout << __FUNCTION__ << " " << m_logName << " begin " << std::endl;
	}
	~LogAspect()
	{
		std::cout<< __FUNCTION__ << " " << m_logName << " end " << std::endl;
	}
};


//模拟一个事务切面
template <class T>
class TransactionAspect : public Aspect<T>
{

private:
	mutex *m_trans;

public:
	TransactionAspect(T* pAction, mutex* m) :Aspect<T>(pAction),m_trans(m)
	{
		std::cout << __FUNCTION__ << " begin " << std::endl;
		m_trans->lock();

	}
	~TransactionAspect()
	{
		m_trans->unlock();
		std::cout << __FUNCTION__ << " end " << std::endl;
	}
};



//测试
class Action
{
public :
	void Go(string goWhat)
	{
		std::cout << __FUNCTION__ << goWhat << std::endl;
	}
};

void TestAOP()
{
	Action alpha;
	LogAspect<Action>(&alpha, "logOne")->Go("三十六计，走为上计");
	std::cout << "\r\n";
	mutex justOne;
	TransactionAspect<Action>(&alpha, &justOne)->Go("一夫当关，万夫莫开");
}