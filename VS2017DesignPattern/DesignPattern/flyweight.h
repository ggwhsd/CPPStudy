#pragma once


#include <iostream>
#include <string>
#include <map>
// 玩家 - 有武器和使命
class IPlayer
{
public:
	virtual ~IPlayer() {}

	// 分配武器
	virtual void assignWeapon(std::string weapon) = 0;

	// 使命
	virtual void mission() = 0;

protected:
	std::string m_task; // 内部状态
	std::string m_weapon; // 外部状态
};

// 恐怖分子
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

// 反恐精英
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


// 用于获取玩家
class PlayerFactory
{
public:
	// 如果 T/CT 对象存在，则直接从享元池获取；否则，创建一个新对象并添加到享元池中，然后返回。
	static IPlayer* getPlayer(std::string type)
	{
		IPlayer *p = NULL;
		if (m_map.find(type) != m_map.end()) {
			p = m_map[type];
		}
		else {
			// 创建 T/CT 对象
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
			// 一旦创建，将其插入到 map 中
			m_map.insert(std::make_pair(type, p));
		}
		return p;
	}

private:
	// 存储 T/CT 对象（享元池）
	static std::map<std::string, IPlayer*> m_map;
};
