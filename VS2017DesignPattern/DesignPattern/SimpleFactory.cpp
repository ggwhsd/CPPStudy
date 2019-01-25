#include "stdafx.h"
#include "SimpleFactory.h"


SimpleFactory::SimpleFactory()
{
};

ICar* SimpleFactory::CreateCar(CAR_TYPE type)
{
	ICar* pCar = NULL;
	switch (type)
	{
	case CAR_TYPE::AUDI_CAR:
		pCar = new AudiCar();
		break;
	case CAR_TYPE::BENZ_CAR:
		pCar = new BenzCar();
		break;
	case CAR_TYPE::BMW_CAR:
		pCar = new BMWCar();
		break;
	default:
		break;
	}
	return pCar;
};


ICar* SimpleFactory::CreateBMW()
{
	ICar* pCar = NULL;
	pCar = new BMWCar();
	return pCar;
}
ICar* SimpleFactory::CreateBenz()
{
	ICar* pCar = NULL;
	pCar = new BenzCar();
	return pCar;
}
ICar* SimpleFactory::CreateAudi()
{
	ICar* pCar = NULL;
	pCar = new AudiCar();
	return pCar;
}
SimpleFactory::~SimpleFactory()
{
};
