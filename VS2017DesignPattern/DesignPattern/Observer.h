#pragma once

#include <iostream>
#include <list>
#include <string>

using namespace std;

// 抽象观察者
class IObserver
{
public:
	virtual void Update(float price) = 0;  // 更新价格
};

// 抽象主题
class ISubject
{
public:
	virtual void Attach(IObserver *) = 0;  // 注册观察者
	virtual void Detach(IObserver *) = 0;  // 注销观察者
	virtual void Notify() = 0;  // 通知观察者
};


// 具体主题
class ConcreteSubject : public ISubject
{
public:
	ConcreteSubject() { m_fPrice = 10.0; }

	void SetPrice(float price) {
		m_fPrice = price;
	}

	void Attach(IObserver *observer) {
		m_observers.push_back(observer);
	}

	void Detach(IObserver *observer) {
		m_observers.remove(observer);
	}

	void Notify() {
		list<IObserver *>::iterator it = m_observers.begin();
		while (it != m_observers.end()) {
			(*it)->Update(m_fPrice);
			++it;
		}
	}

private:
	list<IObserver *> m_observers;  // 观察者列表
	float m_fPrice;  // 价格
};



// 具体观察者
class ConcreteObserver : public IObserver
{
public:
	ConcreteObserver(string name) { m_strName = name; }

	void Update(float price) {
		std::cout << m_strName << " - price: " << price << "\n";
	}

private:
	string m_strName;  // 名字
};
