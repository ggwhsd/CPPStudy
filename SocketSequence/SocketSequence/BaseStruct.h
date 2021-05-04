#pragma once

typedef struct Info
{
	char client_name[10];
	char buffer[5];
	int  age;
	int age2;


}message;
struct Package
{
	int len;
	message msg;
};




void StartClient(int port);

void StartServer(int port);