#pragma once
#include <string>

typedef struct Info
{
	char client_name[20];
	char buffer[5];
	int  age;
	int age2;


}message;
struct Package
{
	int len; //报文中除了len字段以外，其他字段在网络字节流中的长度，方便接收者接收，而无需逐个字节判断是否接收完整。
	message msg;
};




void StartClient(std::string ip, int port, int testCounts);

void StartServer(int port, int testCounts);