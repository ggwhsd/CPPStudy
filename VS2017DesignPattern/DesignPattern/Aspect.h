#pragma once
#include <iostream>
#include <string>
#include <mutex>
using namespace std;
/*
���Ͽ�����һ�ַ��������ù�����������ƣ���ʵ��C++�е�AOP��
���⣬ͨ���������ģʽҲ����ʵ��AOP��ֻ�ǲ���ͨ�á�
*/
template <class T>
class Aspect
{
private:
	T* m_pAction;
protected:
	Aspect(T* pAction) :m_pAction(pAction)
	{}
	//��Ϊ��protected���������������޷�����ջ����
	virtual ~Aspect()
	{
	}
public:
	//����ָ�������
	T * operator->()
	{
		return m_pAction;
	}
};

//ģ��һ����־����
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


//ģ��һ����������
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



//����
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
	LogAspect<Action>(&alpha, "logOne")->Go("��ʮ���ƣ���Ϊ�ϼ�");
	std::cout << "\r\n";
	mutex justOne;
	TransactionAspect<Action>(&alpha, &justOne)->Go("һ�򵱹أ����Ī��");
}