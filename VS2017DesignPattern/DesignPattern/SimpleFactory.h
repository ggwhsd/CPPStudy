#pragma once
#include <string>
using namespace std;

class ICar
{
public:
	virtual string name() = 0;
};

class BMWCar : public ICar
{
public:
	string name()
	{
		return "BMWCar";
	}

};

class BenzCar : public ICar
{
public :
	string name()
	{
		return "BenzCar";
	}
};

class AudiCar : public ICar
{
public:
	string name()
	{
		return "AudiCar";
	}
};


class SimpleFactory
{
public:
	enum CAR_TYPE
	{
		BENZ_CAR,
		BMW_CAR,
		AUDI_CAR
	};

public:
	SimpleFactory();
	ICar* CreateCar(CAR_TYPE);
	ICar* CreateBMW();
	ICar* CreateBenz();
	ICar* CreateAudi();
	~SimpleFactory();
};
