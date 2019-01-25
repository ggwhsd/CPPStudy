#pragma once
#include <iostream>
using namespace std;

class Computer
{
private:
	string _strCpu;
	string _strMainboard;
	string _strRam;
	string _strVideoCard;

public:
	void SetCpu(string cpu) 
	{ _strCpu = cpu; }

	void SetMainBoard(string mainboard)
	{
		_strMainboard = mainboard;
	}
	void SetRam(string Ram)
	{
		_strRam = Ram;
	}
	void SetVideoCard(string VideoCard)
	{
		_strVideoCard = VideoCard;
	}

	string GetCpu()
	{
		return _strCpu;
	}
	string GetMainBoard()
	{
		return _strMainboard;
	}
	string GetRam()
	{
		return _strRam;
	}
	string GetVideoCard()
	{
		return _strVideoCard;
	}
};


class IBuilder
{
public:
	virtual void BuildCpu() = 0;
	virtual void BuildRam() = 0;
	virtual void BuildMainboard() = 0;
	virtual void BuildVideoCard() = 0;
	virtual Computer* GetResult() = 0;
};

class MacBuilder:public IBuilder
{
public:
	MacBuilder() { _pComputer = new Computer(); }
	void BuildCpu() { _pComputer->SetCpu("i5"); }
	void BuildMainboard() { _pComputer->SetMainBoard("Intel"); }
	void BuildRam() { _pComputer->SetRam("DDR4"); }
	void BuildVideoCard() { _pComputer->SetVideoCard("NVIDIA Geforce 9XXXXXXXX"); }
	Computer* GetResult() { return _pComputer; }

private:
	Computer * _pComputer;
};

class MacProBuilder :public IBuilder
{
public:
	MacProBuilder() { _pComputer = new Computer(); }
	void BuildCpu() { _pComputer->SetCpu("i7"); }
	void BuildMainboard() { _pComputer->SetMainBoard("Intel"); }
	void BuildRam() { _pComputer->SetRam("DDR4"); }
	void BuildVideoCard() { _pComputer->SetVideoCard("NVIDIA Geforce 9XXXXXXXX"); }
	Computer* GetResult() { return _pComputer; }

private:
	Computer * _pComputer;
};

//��ʵ�Ҿ��ã���������࣬��ȫ���Բ��ã�
//��create����ֱ�Ӹ�builder�࣬
//��builder���������create������
//�Ҿ���Ҳûʲô������ġ�
class Director
{
public:
	void Create(IBuilder *builder) {
		builder->BuildCpu();
		builder->BuildMainboard();
		builder->BuildRam();
		builder->BuildVideoCard();
	}
};

