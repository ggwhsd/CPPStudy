#pragma once

#include <iostream>
class IElectricalEquipment
{
public:
	virtual ~IElectricalEquipment() {}
	virtual void PowerOn() = 0;
	virtual void PowerOff() = 0;

};

class Light :public IElectricalEquipment
{
	virtual void PowerOn() override {
		std::cout << "Light on\n";
	}
	virtual void PowerOff() override {
		std::cout << "Light off\n";
	}

};

class Fan :public IElectricalEquipment
{
public:
	virtual void PowerOn() override
	{
		std::cout << "Fan is on" << std::endl;
	}
	virtual void PowerOff() override
	{
		std::cout << "Fan is off\n";
	}

};

class ISwitch
{
protected:
	IElectricalEquipment * m_pEe;
public:
	ISwitch(IElectricalEquipment *ee) { m_pEe = ee; }
	virtual ~ISwitch() {}
	virtual void On() = 0;
	virtual void Off() = 0;
};

// 拉链式开关
class PullChainSwitch : public ISwitch
{
public:
	PullChainSwitch(IElectricalEquipment *ee) : ISwitch(ee) {}
	// 用拉链式开关打开电器
	virtual void On() override {
		std::cout << "Switch on the equipment with a pull chain switch." << std::endl;
		m_pEe->PowerOn();
	}
	// 用拉链式开关关闭电器
	virtual void Off() override {
		std::cout << "Switch off the equipment with a pull chain switch." << std::endl;
		m_pEe->PowerOff();
	}
};

// 两位开关
class TwoPositionSwitch : public ISwitch
{
public:
	TwoPositionSwitch(IElectricalEquipment *ee) : ISwitch(ee) {}

	// 用两位开关打开电器
	virtual void On() override {
		std::cout << "Switch on the equipment with a two-position switch." << std::endl;
		m_pEe->PowerOn();
	}

	// 用两位开关关闭电器
	virtual void Off() override {
		std::cout << "Switch off the equipment with a two-position switch." << std::endl;
		m_pEe->PowerOff();
	}
};