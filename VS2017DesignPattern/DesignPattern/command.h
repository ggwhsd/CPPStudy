#pragma once
#include <iostream>
#include <list>
using namespace std;

// ˾��
class Receiver
{
public:
	void takeOrder();  // �ӵ�
	void receipt();  // �տ�
};
// �ӵ�
void Receiver::takeOrder()
{
	std::cout << "Take order..." << std::endl;
}

// �տ�
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



// ����ĳ�����
class Invoker
{
public:
	Invoker();
	void addCmd(Command *cmd);  // �������
	void deleteCmd(Command *cmd);  // ɾ������
	void notify();  // ִ������

private:
	std::list<Command *> m_cmds;  // �������
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

