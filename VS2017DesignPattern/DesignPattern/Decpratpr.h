#pragma once
#include <string>

using namespace std;

// 所有饮料的基类
class IBeverage
{
public:
	virtual string Name() = 0;  // 名称
	virtual double Cost() = 0;  // 价钱
};

// 黑咖啡，属于混合咖啡
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

// 深度烘培咖啡豆
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


// 调味品
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

/********** 具体的饮料（调味品）**********/

// 奶油
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

// 摩卡
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

// 糖浆
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


