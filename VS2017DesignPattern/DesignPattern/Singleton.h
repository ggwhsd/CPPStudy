#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H
#include <iostream>
#include <mutex>
using namespace std;

class Singleton
{
public:

	static Singleton & GetInstance()
	{
		static
			Singleton instance;
		return instance;
	}

	void doSomething()
	{
		cout << __FUNCTION__ << "Singleton Do something" << endl;
	}
private:
	Singleton() {};
	Singleton(Singleton const&);
	Singleton& operator = (const Singleton &);
};


class Singleton_lazy
{
public:
	static Singleton_lazy* GetInstance()
	{
		if (m_p == NULL)
		{
			lock_guard<mutex> lock(m_mutex);
			if (m_p == NULL)
			{
				m_p = new Singleton_lazy();
			}
		}
		return m_p;
	};

	//释放资源的方式，手动
	static void DestoryInstance()
	{
		if (m_p != NULL)
		{
			delete m_p;
			m_p = NULL;
		}
	}

	//自动
	class GC
	{
	public :
		~GC()
		{
			if (m_p != NULL)
			{
				delete m_p;
				m_p = NULL;
				cout << __FUNCTION__ << " deleted " << endl;
			}
		}
		static GC gc;
	};

	void doSomething()
	{
		cout  <<__FUNCTION__ <<" Singleton_lazy Do something" << endl;
	}
private:
	Singleton_lazy() {};
private:
	static Singleton_lazy * m_p;
	static mutex m_mutex;

};






#endif