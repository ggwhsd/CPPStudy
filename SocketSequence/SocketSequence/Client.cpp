#include "BaseStruct.h"
#include <winsock2.h>  
#include <stdio.h>  



void SetPackage(Package& p)
{
	p.len = sizeof(Package) - 4;
	strcpy(p.msg.client_name, "12345");
	strcpy(p.msg.buffer, "123");
	p.msg.age = 0x00000001;
	p.msg.age2 = 2;

}

//将结构转换为字节流,强制解析
int encodePackageToBufferBytes(char *send_buf, Package& p)
{
	int len = sizeof(Package);
	memcpy(send_buf, &p, len);
	return len;
}


//第二种方法
int encodePackageToBufferBytes2(char *send_buf, Package& p)
{
	
	return 0;
}
void StartClient(int port)
{
	WSADATA WSAData;
	SOCKET sock;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ClientAddr;
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = htons(port);
	ClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(sock, (sockaddr*)&ClientAddr, sizeof(ClientAddr));

	char snd_buf[1024] = { 0 };

	Package p;
	SetPackage(p);
	int send_len = encodePackageToBufferBytes(snd_buf, p);
	send(sock, snd_buf, send_len, 0);


	closesocket(sock);
	WSACleanup();

}