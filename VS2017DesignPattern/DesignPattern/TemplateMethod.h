#pragma once
#include <iostream>
using namespace std;

class Company {
public:
	virtual ~Company() {};
	void Recruit() {
		cout << "--begin--" << endl;
		CareerTalk();
		ReceiveResume();
		Interview();
		Offer();
		std::cout << "---------- End ----------" << std::endl;
	}

	void CareerTalk() {
		std::cout << "宣讲会" << std::endl;
	}
	void ReceiveResume()
	{
		std::cout << "接收简历" << std::endl;
	}
	virtual void Interview() = 0;

	virtual void Offer() = 0;

};

class Alibaba : public Company
{
public:
	virtual void Interview() override {
		std::cout << "First interview -> Second interview -> Third interview" << std::endl;
	}

	virtual void Offer() override {
		std::cout << "30W" << std::endl;
	}
};

class Tencent : public Company
{
public:
	virtual void Interview() override {
		std::cout << "First interview -> Second interview" << std::endl;
	}

	virtual void Offer() override {
		std::cout << "25W" << std::endl;
	}
};