#pragma once
/*
������ģʽ��Adapter Pattern����һ�ֲ���ģʽ��
��һ����Ľӿ�ת���ɿͻ�ϣ��������һ���ӿڣ�
�Ӷ�ʹԭ�����ڽӿڲ����ݶ�����һ�����������һ������
*/
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

#include <iostream>
using namespace std;

class IRussiaSocket
{
public:
	virtual void Charge() = 0;
};

class OwnCharger
{
public:
	void ChargeWithFeetFlat()
	{
		cout << "Chargewithfeetflat" << endl;
	}
};

class PowerAdapter :public IRussiaSocket
{
public:
	PowerAdapter() : m_pCharger(new OwnCharger()) {}
	~PowerAdapter() {
		SAFE_DELETE(m_pCharger);
	}
	void Charge() {
		//  ʹ���Դ��ĳ���������ű��ͣ����
		m_pCharger->ChargeWithFeetFlat();
	}

private:
	OwnCharger * m_pCharger;  // ������Ҫ������Ľӿڶ��� - �Դ��ĳ����
};