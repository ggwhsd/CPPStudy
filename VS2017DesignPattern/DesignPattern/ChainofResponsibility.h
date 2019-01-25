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
			std::cout << "Manager 批准了 " << days << " 天假" << std::endl;
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
			std::cout << "Manager 批准了 " << days << " 天假" << std::endl;
		}
		else {
			m_pNext->HandleRequest(days);
		}
	}

};

// 总裁
class CEO : public IHandler
{
public:
	CEO() {}
	~CEO() {}
	virtual void HandleRequest(int days) override {
		if (days <= 7) {
			std::cout << "CEO 批准了 " << days << " 天假" << std::endl;
		}
		else {
			std::cout << "给你放长假，以后不用来上班啦！" << std::endl;
		}
	}
};