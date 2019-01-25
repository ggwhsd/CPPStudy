#pragma once


#include <iostream>
#include <string>
#include <map>
// ��� - ��������ʹ��
class IPlayer
{
public:
	virtual ~IPlayer() {}

	// ��������
	virtual void assignWeapon(std::string weapon) = 0;

	// ʹ��
	virtual void mission() = 0;

protected:
	std::string m_task; // �ڲ�״̬
	std::string m_weapon; // �ⲿ״̬
};

// �ֲ�����
class Terrorist : public IPlayer
{
public:
	Terrorist() {
		m_task = "Plant a bomb";
	}

	virtual void assignWeapon(std::string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		std::cout << "Terrorist with weapon " + m_weapon + "," + " Task is " + m_task << std::endl;
	}
};

// ���־�Ӣ
class CounterTerrorist : public IPlayer
{
public:
	CounterTerrorist() {
		m_task = "Diffuse bomb";
	}

	virtual void assignWeapon(std::string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		std::cout << "Counter Terrorist with weapon " + m_weapon + "," + " Task is " + m_task << std::endl;
	}
};


// ���ڻ�ȡ���
class PlayerFactory
{
public:
	// ��� T/CT ������ڣ���ֱ�Ӵ���Ԫ�ػ�ȡ�����򣬴���һ���¶�����ӵ���Ԫ���У�Ȼ�󷵻ء�
	static IPlayer* getPlayer(std::string type)
	{
		IPlayer *p = NULL;
		if (m_map.find(type) != m_map.end()) {
			p = m_map[type];
		}
		else {
			// ���� T/CT ����
			if (type == "T") {
				std::cout << "Terrorist Created" << std::endl;
				p = new Terrorist();
			}
			else if (type == "CT") {
				std::cout << "Counter Terrorist Created" << std::endl;
				p = new CounterTerrorist();
			}
			else {
				std::cout << "Unreachable code!" << std::endl;
			}
			// һ��������������뵽 map ��
			m_map.insert(std::make_pair(type, p));
		}
		return p;
	}

private:
	// �洢 T/CT ������Ԫ�أ�
	static std::map<std::string, IPlayer*> m_map;
};
