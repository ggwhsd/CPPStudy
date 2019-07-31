#pragma once
#include <iostream>
using namespace std;
class IStrategy {
public:
	virtual void Travel() = 0;
	IStrategy()
	{
		cout << __FUNCTION__ << endl;
	}
	virtual ~IStrategy()
	{
		cout << __FUNCTION__ << endl;
	}
};

class BikeStrategy : public IStrategy {
public:
	virtual void Travel() override {
		cout << "travel by bike" << endl;
	}

	BikeStrategy()
	{
		cout << __FUNCTION__ << endl;
	}
	~BikeStrategy()
	{
		cout << __FUNCTION__ << endl;
	}

};

class CarStrategy : public IStrategy
{
public:
	virtual void Travel() override {
		cout << "Travel by car" << endl;
	}
};

class TrainStrategy : public IStrategy
{
public:
	virtual void Travel() override {
		cout << "Travel by train" << endl;
	}
};


class Context
{
private:
	IStrategy * m_pStrategy;
public:
	Context(IStrategy * strategy) {
		m_pStrategy = strategy;
	}
	void Travel() {
		m_pStrategy->Travel();
	}
};