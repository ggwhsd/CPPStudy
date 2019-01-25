#include "stdafx.h"
#include "AbstractFactory.h"

using namespace AF;
AbstractFactory::AbstractFactory()
{
}

AbstractFactory* AbstractFactory::CreateFactory(FACTORY_TYPE factory)
{
	AbstractFactory *pFactory = NULL;
	switch (factory) {
	case FACTORY_TYPE::BENZ_FACTORY:  // 奔驰工厂
		pFactory = new BenzFactory();
		break;
	case FACTORY_TYPE::BMW_FACTORY:  // 宝马工厂
		pFactory = new BmwFactory();
		break;
	case FACTORY_TYPE::AUDI_FACTORY:  // 奥迪工厂
		pFactory = new AudiFactory();
		break;
	default:
		break;
	}
	return pFactory;
}

AbstractFactory::~AbstractFactory()
{
}
