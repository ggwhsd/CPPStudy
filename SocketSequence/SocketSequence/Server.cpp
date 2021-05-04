#include "BaseStruct.h"
#include <winsock2.h>  
#include <stdio.h>  

static message msg;

//将字节流转换为结构
Package* decodeBytesToPackage(char *buf)
{
	// 接收到结构，强制类型转换
	Package *p = (Package*)buf;

	printf("%d \n", p->len);
	printf("%s \n", p->msg.client_name);
	printf("%s \n", p->msg.buffer);
	printf("%d \n", p->msg.age);
	printf("%d \n", p->msg.age2);
	return p;

}
void StartServer(int port)
{

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port);
	ServerAddr.sin_addr.s_addr = INADDR_ANY;

	bind(sock, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr));
	listen(sock, 10);
	SOCKET msgsock;
	char buf[1024] = { 0 };
	msgsock = accept(sock, (LPSOCKADDR)0, (int *)0);

		recv(msgsock, buf, sizeof(buf), 0);
		//测试而已，不考虑粘包问题了。
	decodeBytesToPackage(buf);

	closesocket(sock);
	WSACleanup();
	system("pause");

}