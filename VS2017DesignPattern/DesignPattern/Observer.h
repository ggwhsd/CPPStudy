#pragma once

#include <iostream>
#include <list>
#include <string>

using namespace std;

// ����۲���
class IObserver
{
public:
	virtual void Update(float price) = 0;  // ���¼۸�
};

// ��������
class ISubject
{
public:
	virtual void Attach(IObserver *) = 0;  // ע��۲���
	virtual void Detach(IObserver *) = 0;  // ע���۲���
	virtual void Notify() = 0;  // ֪ͨ�۲���
};


// ��������
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
	list<IObserver *> m_observers;  // �۲����б�
	float m_fPrice;  // �۸�
};



// ����۲���
class ConcreteObserver : public IObserver
{
public:
	ConcreteObserver(string name) { m_strName = name; }

	void Update(float price) {
		std::cout << m_strName << " - price: " << price << "\n";
	}

private:
	string m_strName;  // ����
};
