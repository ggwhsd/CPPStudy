// SocketSequence.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "BaseStruct.h"
#include "Utils.h"
#pragma comment(lib,"ws2_32.lib")


int main()
{
	char buffer[4];
	convertToCharFromInt_BigEnd(0x01020304, buffer);
	int value;
	convertToIntFromChar_BigEnd(buffer, value);
	convertToCharFromInt_LittleEnd(0x01020304, buffer);
	convertToIntFromChar_LittleEnd(buffer, value);

	convertToCharFromInt_LittleEnd(0x00000180, buffer);
	convertToIntFromChar_LittleEnd(buffer, value);





	IsLitten();
	std::cout << "1:client,\r\n2:server\r\n:";
	int choice;
	std::cin >> choice;
	if (choice == 1)
	{
		//client
		std::cout << "\r\n启动客户端11111端口";
		StartClient(11111);
	}
	else
	{
		std::cout << "\r\n启动服务端11111端口";
		StartServer(11111);
	}
    std::cout << "Hello World!\n";
}

