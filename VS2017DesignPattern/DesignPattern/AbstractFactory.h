#pragma once
#include "SimpleFactory.h"
#include <string>
using namespace std;
namespace AF{
	class IBike
	{
	public:
		virtual string name() = 0;
	};

	class BenzBike : public IBike
	{
	public:
		string name()
		{
			return "Benz Bike";
		}

	};

	class BmwBike : public IBike
	{
	public:
		string name()
		{
			return "Bmw Bike";
		}

	};


	class AudiBike : public IBike
	{
	public:
		string name()
		{
			return "AudiBike Bike";
		}
	};




	class AbstractFactory
	{

	public:
		enum FACTORY_TYPE
		{
			BENZ_FACTORY,
			BMW_FACTORY,
			AUDI_FACTORY
		};
		virtual ICar* CreateCar() = 0;
		virtual IBike* CreateBike() = 0;
		static
			AbstractFactory* CreateFactory(FACTORY_TYPE);
		AbstractFactory();
		~AbstractFactory();
	};

	class BenzFactory :public AbstractFactory
	{
	public:
		ICar * CreateCar()
		{
			return new BenzCar();
		}
		IBike* CreateBike()
		{
			return new BenzBike();
		}
	};

	class BmwFactory : public AbstractFactory
	{
	public:
		ICar * CreateCar()
		{
			return new BMWCar();
		}
		IBike* CreateBike()
		{
			return new BmwBike();
		}
	};

	class AudiFactory : public AbstractFactory
	{
	public:
		ICar * CreateCar()
		{
			return new AudiCar();
		}
		IBike* CreateBike()
		{
			return new AudiBike();
		}
	};
}