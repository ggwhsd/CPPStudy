#pragma once
#include <iostream>
#include <list>
using namespace std;

// 司机
class Receiver
{
public:
	void takeOrder();  // 接单
	void receipt();  // 收款
};
// 接单
void Receiver::takeOrder()
{
	std::cout << "Take order..." << std::endl;
}

// 收款
void Receiver::receipt()
{
	std::cout << "Receipt..." << std::endl;
}
;
class Command {
protected :
	Receiver * m_pReceiver;

public:
	Command(Receiver * receiver):m_pReceiver(receiver)
	{

	};
	virtual void execute() = 0;
};

class TakeCommand : public Command
{
public:
	TakeCommand(Receiver* receiver):Command(receiver)
	{
		
	}

	void execute()
	{
		m_pReceiver->takeOrder();
	}
};

class PayCommand : public Command
{
public :
	PayCommand(Receiver* receiver) :Command(receiver)
	{}
	void execute()
	{
		
		m_pReceiver->receipt();
	}
};



// 命令的持有者
class Invoker
{
public:
	Invoker();
	void addCmd(Command *cmd);  // 添加命令
	void deleteCmd(Command *cmd);  // 删除命令
	void notify();  // 执行命令

private:
	std::list<Command *> m_cmds;  // 命令队列
};


Invoker::Invoker()
{

}

void Invoker::addCmd(Command *cmd)
{
	m_cmds.push_back(cmd);
}

void Invoker::deleteCmd(Command *cmd)
{
	m_cmds.remove(cmd);
}

void Invoker::notify()
{
	std::list<Command *>::iterator it = m_cmds.begin();
	while (it != m_cmds.end()) {
		(*it)->execute();
		++it;
	}
}

