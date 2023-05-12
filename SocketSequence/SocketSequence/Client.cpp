#include "BaseStruct.h"
#include <winsock2.h>  
#include <stdio.h>  
#include <string>
#include "Utils.h"


void SetPackage(Package& p)
{


	strcpy(p.msg.client_name, "1");
	strcpy(p.msg.buffer, "123");
	p.msg.age = 0x00000001;
	p.msg.age2 =1;
	//若使用指针自动强制解析（必须都为小端序的服务器或者都为大端序，否则解析出错），则长度如下，如果是逐个字段自定义解析，则需要解析之后才知道需要传输多少字节
	p.len = sizeof(Package) - 4;

}

//将结构转换为字节流,强制解析
int encodePackageToBufferBytes(char *send_buf, Package& p)
{
	int len = sizeof(Package);
	memcpy(send_buf, &p, len);
	return len;
}


//第二种方法，逐个字段编码
int encodePackageToBufferBytes2(char *send_buf, Package& p)
{
	int totalLen = 0;
	char *send_buf_old = send_buf;
	
	send_buf += 4;
	//这里将固定数组client_name只拷贝了有效的部分数据，减少了网络传输空间。
	strcpy(send_buf, p.msg.client_name);
	int str_len = strlen(p.msg.client_name)+1;
	send_buf += str_len;
	totalLen += str_len;

	strcpy(send_buf, p.msg.buffer);
	str_len = strlen(p.msg.buffer)+1;
	send_buf += str_len;
	totalLen += str_len;

	convertToCharFromInt_LittleEnd(p.msg.age, send_buf);
	send_buf += 4;
	totalLen += 4;

	convertToCharFromInt_LittleEnd(p.msg.age2, send_buf);
	send_buf += 4;
	totalLen += 4;

	p.len = totalLen;
	convertToCharFromInt_LittleEnd(p.len, send_buf_old);
	totalLen += 4;
	return totalLen;
}



void StartClient(std::string hostIP,int port, int testCounts)
{
	WSADATA WSAData;
	SOCKET sock;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ClientAddr;
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = htons(port);
	ClientAddr.sin_addr.s_addr = inet_addr(hostIP.c_str());
	connect(sock, (sockaddr*)&ClientAddr, sizeof(ClientAddr));

	char snd_buf[1024] = { 0 };

	Package p;
	SetPackage(p);
	//int send_len = encodePackageToBufferBytes(snd_buf, p);
	//send(sock, snd_buf, send_len, 0);
	printf("start send%s", getNow().c_str());
	while (testCounts > 0)
	{
		testCounts--;
		p.msg.age2 = 1;
		int sendCount = 1000000;
		while (sendCount > 0)
		{
			sendCount--;
			memset(snd_buf, 0, 1024);

			int send_len = encodePackageToBufferBytes2(snd_buf, p);
			send(sock, snd_buf, send_len, 0);
			p.msg.age2 += 1;
			strcpy(p.msg.client_name, std::to_string(p.msg.age2).c_str());
		}
	}
	printf("stop send%s", getNow().c_str());
	closesocket(sock);
	WSACleanup();
}