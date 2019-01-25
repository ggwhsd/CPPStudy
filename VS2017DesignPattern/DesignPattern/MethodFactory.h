#pragma once
#include "SimpleFactory.h"



class MethodFactory
{
public:
	virtual ICar* CreateCar() = 0;

};

class BenzFactory :public MethodFactory
{
public:
	ICar * CreateCar()
	{
		return new BenzCar();
	}
};

class BmwFactory : public MethodFactory
{
public:
	ICar * CreateCar()
	{
		return new BMWCar();
	}
};

class AudiFactory : public MethodFactory
{
public:
	ICar * CreateCar()
	{
		return new AudiCar();
	}
};