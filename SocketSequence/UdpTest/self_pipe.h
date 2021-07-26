#pragma once
#include<iostream>
#include<WinSock2.h>

void StartPipe()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);//错误会返回WSASYSNOTREADY
	if (err != 0)
	{
		return;
	}
	if (LOBYTE(wsaData.wVersion) != 1 ||     //低字节为主版本
		HIBYTE(wsaData.wVersion) != 1)      //高字节为副版本
	{
		WSACleanup();
		return;
	}
	std::cout << ("self_pipe is operating!\n\n");
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;     //定义sockSrv发送和接收数据包的地址
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);   //inet_addr("127.0.0.1")
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = 0;
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	sockaddr m_addr;
	int m_addr_len = sizeof(m_addr);
	memset(&m_addr, 0, sizeof(m_addr));
	getsockname(sockSrv, &m_addr, &m_addr_len);
	std::cout << m_addr.sa_data << std::endl;

	connect(sockSrv, &m_addr, m_addr_len);


	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[100];

	while (1)
	{
		std::cout << "pls input data: \n";
		std::cin >> (sendBuf);

		send(sockSrv, sendBuf, strlen(sendBuf) + 1, 0);
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		if ('q' == recvBuf[0])
		{
			
			std::cout << "quit" << std::endl;
			break;
		}
		sprintf_s(tempBuf, "%s say : %s", inet_ntoa(addrClient.sin_addr), recvBuf);
		std::cout << tempBuf << std::endl;;

		

	}
	closesocket(sockSrv);
	WSACleanup();
}