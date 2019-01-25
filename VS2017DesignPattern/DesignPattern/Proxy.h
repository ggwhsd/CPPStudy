#pragma once
#include <iostream>
using namespace std;

class ITelco
{
public:
	virtual ~ITelco() {};
	virtual void Recharge(int money) = 0;
};

class CMCC : public ITelco
{
public:
	void Recharge(int money) override {
		std::cout << "Recharge" << money << std::endl;
	}
};

class Proxy : public ITelco
{
private:
	CMCC * m_pCMCC;
public:
	Proxy() :m_pCMCC(NULL) {}
	~Proxy() { delete m_pCMCC; }
	// µÍÓÚ 50 ²»³ä
	void Recharge(int money) override {
		if (money >= 50) {
			if (m_pCMCC == NULL)
				m_pCMCC = new CMCC();
			m_pCMCC->Recharge(money);
		}
		else {
			std::cout << "Sorry, too little money" << std::endl;
		}
	}
};