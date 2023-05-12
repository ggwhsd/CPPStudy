#include "BaseStruct.h"
#include "Utils.h"
#include <winsock2.h>  
#include <stdio.h>  
#include <memory>

static message msg;

//强制转换，将字节流转换为结构
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



static int decode_recv_index = -1;
static std::shared_ptr<Package> p = nullptr;
static char *decode_recv_buf = nullptr;
static char recv_buf[1030] = { 0 };
static int recv_len = 0;
//第二种方法，逐个字节解码成对应字段
std::shared_ptr<Package> decodePackageToBufferBytes2(char *recv, int len)
{

	if (len >= 0)
	{
		memcpy(recv_buf + recv_len, recv, len);
		recv_len += len;
	}

	if(decode_recv_buf==nullptr)
		decode_recv_buf = recv_buf;

	if(recv_len<=4)
	{
		//printf("%d 接收头长度未知，继续等待\n", recv_len);
		return nullptr;
	}
	if (decode_recv_index == -1)
	{
		p = std::make_shared<Package>();
		convertToIntFromChar_LittleEnd(decode_recv_buf, p->len);
		decode_recv_index += 4;
		decode_recv_buf += 4;
		
		
	}
	if (decode_recv_index >= 3)
	{
		int len_body = p->len;

		if (recv_len - 4 < len_body)
		{
			//因为编码时候，只有报文体有长度，每个字段并没有长度告知，所以等所有字段接收后再处理起来，则比较简单。
			//printf("%d %d接收body未结束，继续等待\n", recv_len, p->len);
			return nullptr;
		}
		else
		{
			//printf("%d 接收body结束，可以处理\n", recv_len);
		}
	}

	
	strcpy(p->msg.client_name, decode_recv_buf);
	int str_len = strlen(p->msg.client_name) + 1;
	decode_recv_index += str_len;
	decode_recv_buf += str_len;

	strcpy(p->msg.buffer,decode_recv_buf);
	str_len = strlen(p->msg.buffer) + 1;
	decode_recv_index += str_len;
	decode_recv_buf += str_len;

	
	convertToIntFromChar_LittleEnd(decode_recv_buf, p->msg.age);
	decode_recv_index += 4;
	decode_recv_buf += 4;

	convertToIntFromChar_LittleEnd(decode_recv_buf, p->msg.age2);
	decode_recv_index += 4;
	decode_recv_buf += 4;
	//printf("rece_index[%d] , p-len[%d], p->msg.age2[%d] \r\n", decode_recv_index,p->len, p->msg.age2);
	if (p->msg.age2 != atoi(p->msg.client_name))
	{
		printf("出错，理应相同的测试数据 %d %d", p->msg.age2, atoi(p->msg.client_name));
	}
	
	memmove(recv_buf, decode_recv_buf, recv_len - decode_recv_index - 1);
	recv_len = recv_len - decode_recv_index - 1;
	decode_recv_buf = nullptr;
	decode_recv_index = -1;
	
	return p;
}


void StartServer(int port,int testCounts)
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
#pragma region  单个socket接收

	printf("start recv%s", getNow().c_str());
	int len_recv = -1;
	len_recv = recv(msgsock, buf, sizeof(buf), 0);
	
	//decodeBytesToPackage(buf);//测试而已，不考虑粘包问题了。
	while (len_recv > 0)
	{
		
		auto package = decodePackageToBufferBytes2(buf, len_recv);//考虑粘包
		while (package != nullptr)
		{
			
			package = decodePackageToBufferBytes2(nullptr, 0);
		}
		len_recv = recv(msgsock, buf , sizeof(buf), 0);
		
			
		
	}
	printf("end recv%s", getNow().c_str());
	printf("测试结束");
	closesocket(sock);


#pragma endregion

	



	WSACleanup();
	system("pause");

}