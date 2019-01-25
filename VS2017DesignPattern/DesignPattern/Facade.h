#pragma once
#include <iostream>
#include <string>
#include <windows.h>
//外观模式

const std::string c_stateToStrCourier[] = { "收到", "验证可达性", "分配人员", "派送包裹", "获取交货确认", "完成" };
const std::string c_stateToStrVendor[] = { "收到", "确认库存", "从仓库得到物品", "包装", "联系快递员", "完成" };
const std::string c_stateToStrOrderTeam[] = { "收到", "确认付款", "联系供应商", "完成" };
const int c_nMsec = 300;  // 休眠时间（毫秒） - Sleep(c_nMsec) 处可以替换为一些有用的代码

// 订单团队
class OrderTeam
{
private:
	enum States {
		Received,  // 收到
		VerifyPayment,  // 确认付款
		ContactVendor,  // 联系供应商
		Complete  // 完成
	};
	int m_nState;

public:
	void submitRequest()
	{
		m_nState = 0;
	}

	bool checkStatus()
	{
		std::cout << "订单团队-当前状态" << c_stateToStrOrderTeam[m_nState] << std::endl;
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
	// 检测状态
	bool checkStatus() {
		std::cout << "供应商 - 当前状态：" << c_stateToStrVendor[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}
private:
	enum States {
		Received,  // 收到
		VerifyInventory,  // 确认库存
		GetItemFromWareHouse,  // 从仓库得到物品
		PackItem,  // 包装
		ContactCourier,  // 联系快递员
		Complete  // 完成
	};
	int m_nState;
};


// 快递员
class Courier
{
public:
	// 将请求转发给快递员
	void submitRequest() {
		m_nState = 0;
	}

	// 检测状态
	bool checkStatus() {
		std::cout << "快递员 - 当前状态：" << c_stateToStrCourier[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // 收到
		VerifyReachbility,  // 验证可达性
		AssignPerson,  // 分配人员
		DispatchPackage,  // 派送包裹
		GetDeliveryConfirmation,  // 获取交货确认
		Complete  // 完成
	};
	int m_nState;
};

// 网购外观
class OnlineShoppingFacade
{
private:
	enum States {
		Received,  // 收到
		SubmittedToOrderTeam,  // 提交给订单团队
		SubmittedToVendor,  // 提交给供应商
		SubmittedToCourier  // 提交给快递员
	};

	int m_nState;  // 订单状态
	int m_nCount;  // 跟踪次数

	OrderTeam m_order;
	Vendor m_vendor;
	Courier m_courier;

public:
	OnlineShoppingFacade() {
		m_nCount = 0;
	}

	// 返回跟踪次数
	int followupNum() {
		return m_nCount;
	}

	// 提交订单
	void submitRequest() {
		m_nState = 0;
	}

	// 跟踪订单
	bool checkStatus() {
		// 收到订单请求
		switch (m_nState) {
		case Received:
			m_nState++;
			// 将请求转发给订单团队
			m_order.submitRequest();
			std::cout << "********** 提交给订单团队，跟踪次数：" << m_nCount << " **********" << std::endl;
			break;
		case SubmittedToOrderTeam:
			// 如果订单团队完成验证，则向供应商发出请求
			if (m_order.checkStatus()) {
				m_nState++;
				m_vendor.submitRequest();
				std::cout << "********** 提交给供应商，跟踪次数：" << m_nCount << " **********" << std::endl;
			}
			break;
		case SubmittedToVendor:
			// 如果供应商已将包裹打包，将其转发给快递员
			if (m_vendor.checkStatus()) {
				m_nState++;
				m_courier.submitRequest();
				std::cout << "********** 提交给快递员，跟踪次数：" << m_nCount << " **********" << std::endl;
			}
			break;
		case SubmittedToCourier:
			// 如果包裹交付，订单完成
			if (m_courier.checkStatus())
				return true;
		default:
			break;
		}

		m_nCount++;

		// 订单未完成
		return false;
	}


};

