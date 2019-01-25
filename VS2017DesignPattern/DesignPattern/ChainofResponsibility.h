#pragma once
#include <iostream>
using namespace std;

class IHandler
{

public:
	IHandler() { m_pNext = NULL; }
	virtual ~IHandler() {};
	void SetNext(IHandler* next) { m_pNext = next; }
	virtual void HandleRequest(int days) = 0;
protected:
	IHandler * m_pNext;
};

class Manager : public IHandler
{
public:
	Manager() {}
	~Manager() {}
	virtual void HandleRequest(int days) override {
		if (days <= 1) {
			std::cout << "Manager ��׼�� " << days << " ���" << std::endl;
		}
		else {
			m_pNext->HandleRequest(days);
		}
	}
};

class DirectorW : public IHandler
{
public:
	DirectorW() {}
	~DirectorW() {}
	virtual void HandleRequest(int days) override {
		if (days <= 1) {
			std::cout << "Manager ��׼�� " << days << " ���" << std::endl;
		}
		else {
			m_pNext->HandleRequest(days);
		}
	}

};

// �ܲ�
class CEO : public IHandler
{
public:
	CEO() {}
	~CEO() {}
	virtual void HandleRequest(int days) override {
		if (days <= 7) {
			std::cout << "CEO ��׼�� " << days << " ���" << std::endl;
		}
		else {
			std::cout << "����ų��٣��Ժ������ϰ�����" << std::endl;
		}
	}
};