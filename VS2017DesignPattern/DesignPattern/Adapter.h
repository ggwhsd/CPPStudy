#pragma once
/*
适配器模式（Adapter Pattern）是一种补救模式，
将一个类的接口转换成客户希望的另外一个接口，
从而使原本由于接口不兼容而不能一起工作的类可以一起工作。
*/
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

#include <iostream>
using namespace std;

class IRussiaSocket
{
public:
	virtual void Charge() = 0;
};

class OwnCharger
{
public:
	void ChargeWithFeetFlat()
	{
		cout << "Chargewithfeetflat" << endl;
	}
};

class PowerAdapter :public IRussiaSocket
{
public:
	PowerAdapter() : m_pCharger(new OwnCharger()) {}
	~PowerAdapter() {
		SAFE_DELETE(m_pCharger);
	}
	void Charge() {
		//  使用自带的充电器（两脚扁型）充电
		m_pCharger->ChargeWithFeetFlat();
	}

private:
	OwnCharger * m_pCharger;  // 持有需要被适配的接口对象 - 自带的充电器
};