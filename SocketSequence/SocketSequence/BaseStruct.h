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
	int len; //�����г���len�ֶ����⣬�����ֶ��������ֽ����еĳ��ȣ���������߽��գ�����������ֽ��ж��Ƿ����������
	message msg;
};




void StartClient(std::string ip, int port, int testCounts);

void StartServer(int port, int testCounts);