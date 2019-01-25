#pragma once
#include <string>

using namespace std;

// �������ϵĻ���
class IBeverage
{
public:
	virtual string Name() = 0;  // ����
	virtual double Cost() = 0;  // ��Ǯ
};

// �ڿ��ȣ����ڻ�Ͽ���
class HouseBlend : public IBeverage
{
public:
	string Name() {
		return "HouseBlend";
	}

	double Cost() {
		return 30.0;
	}
};

// ��Ⱥ��࿧�ȶ�
class DarkRoast : public IBeverage
{
public:
	string Name() {
		return "DarkRoast";
	}

	double Cost() {
		return 28.5;
	}
};


// ��ζƷ
class CondimentDecorator : public IBeverage
{
public:
	CondimentDecorator(IBeverage *beverage) : m_pBeverage(beverage) {}

	string Name() {
		return m_pBeverage->Name();
	}

	double Cost() {
		return m_pBeverage->Cost();
	}

protected:
	IBeverage * m_pBeverage;
};

/********** ��������ϣ���ζƷ��**********/

// ����
class Cream : public CondimentDecorator
{
public:
	Cream(IBeverage *beverage) : CondimentDecorator(beverage) {}

	string Name() {
		return m_pBeverage->Name() + " Cream";
	}

	double Cost() {
		return m_pBeverage->Cost() + 3.5;
	}
};

// Ħ��
class Mocha : public CondimentDecorator
{
public:
	Mocha(IBeverage *beverage) : CondimentDecorator(beverage) {}

	string Name() {
		return m_pBeverage->Name() + " Mocha";
	}

	double Cost() {
		return m_pBeverage->Cost() + 2.0;
	}
};

// �ǽ�
class Syrup : public CondimentDecorator
{
public:
	Syrup(IBeverage *beverage) : CondimentDecorator(beverage) {}

	string Name() {
		return m_pBeverage->Name() + " Syrup";
	}

	double Cost() {
		return m_pBeverage->Cost() + 3.0;
	}
};


