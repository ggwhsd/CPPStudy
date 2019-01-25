#pragma once
#include <iostream>
#include <string>
#include <windows.h>
//���ģʽ

const std::string c_stateToStrCourier[] = { "�յ�", "��֤�ɴ���", "������Ա", "���Ͱ���", "��ȡ����ȷ��", "���" };
const std::string c_stateToStrVendor[] = { "�յ�", "ȷ�Ͽ��", "�Ӳֿ�õ���Ʒ", "��װ", "��ϵ���Ա", "���" };
const std::string c_stateToStrOrderTeam[] = { "�յ�", "ȷ�ϸ���", "��ϵ��Ӧ��", "���" };
const int c_nMsec = 300;  // ����ʱ�䣨���룩 - Sleep(c_nMsec) �������滻ΪһЩ���õĴ���

// �����Ŷ�
class OrderTeam
{
private:
	enum States {
		Received,  // �յ�
		VerifyPayment,  // ȷ�ϸ���
		ContactVendor,  // ��ϵ��Ӧ��
		Complete  // ���
	};
	int m_nState;

public:
	void submitRequest()
	{
		m_nState = 0;
	}

	bool checkStatus()
	{
		std::cout << "�����Ŷ�-��ǰ״̬" << c_stateToStrOrderTeam[m_nState] << std::endl;
		Sleep(c_nMsec);
		m_nState++;
		return (m_nState == Complete);
	}
	
};

class Vendor
{
public :
	void submitRequest()
	{
		m_nState = 0;
	}
	// ���״̬
	bool checkStatus() {
		std::cout << "��Ӧ�� - ��ǰ״̬��" << c_stateToStrVendor[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}
private:
	enum States {
		Received,  // �յ�
		VerifyInventory,  // ȷ�Ͽ��
		GetItemFromWareHouse,  // �Ӳֿ�õ���Ʒ
		PackItem,  // ��װ
		ContactCourier,  // ��ϵ���Ա
		Complete  // ���
	};
	int m_nState;
};


// ���Ա
class Courier
{
public:
	// ������ת�������Ա
	void submitRequest() {
		m_nState = 0;
	}

	// ���״̬
	bool checkStatus() {
		std::cout << "���Ա - ��ǰ״̬��" << c_stateToStrCourier[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // �յ�
		VerifyReachbility,  // ��֤�ɴ���
		AssignPerson,  // ������Ա
		DispatchPackage,  // ���Ͱ���
		GetDeliveryConfirmation,  // ��ȡ����ȷ��
		Complete  // ���
	};
	int m_nState;
};

// �������
class OnlineShoppingFacade
{
private:
	enum States {
		Received,  // �յ�
		SubmittedToOrderTeam,  // �ύ�������Ŷ�
		SubmittedToVendor,  // �ύ����Ӧ��
		SubmittedToCourier  // �ύ�����Ա
	};

	int m_nState;  // ����״̬
	int m_nCount;  // ���ٴ���

	OrderTeam m_order;
	Vendor m_vendor;
	Courier m_courier;

public:
	OnlineShoppingFacade() {
		m_nCount = 0;
	}

	// ���ظ��ٴ���
	int followupNum() {
		return m_nCount;
	}

	// �ύ����
	void submitRequest() {
		m_nState = 0;
	}

	// ���ٶ���
	bool checkStatus() {
		// �յ���������
		switch (m_nState) {
		case Received:
			m_nState++;
			// ������ת���������Ŷ�
			m_order.submitRequest();
			std::cout << "********** �ύ�������Ŷӣ����ٴ�����" << m_nCount << " **********" << std::endl;
			break;
		case SubmittedToOrderTeam:
			// ��������Ŷ������֤������Ӧ�̷�������
			if (m_order.checkStatus()) {
				m_nState++;
				m_vendor.submitRequest();
				std::cout << "********** �ύ����Ӧ�̣����ٴ�����" << m_nCount << " **********" << std::endl;
			}
			break;
		case SubmittedToVendor:
			// �����Ӧ���ѽ��������������ת�������Ա
			if (m_vendor.checkStatus()) {
				m_nState++;
				m_courier.submitRequest();
				std::cout << "********** �ύ�����Ա�����ٴ�����" << m_nCount << " **********" << std::endl;
			}
			break;
		case SubmittedToCourier:
			// ��������������������
			if (m_courier.checkStatus())
				return true;
		default:
			break;
		}

		m_nCount++;

		// ����δ���
		return false;
	}


};

