// SocketSequence.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "BaseStruct.h"

#pragma comment(lib,"ws2_32.lib")

void IsLitten()
{
	unsigned short age = 0x1234;
	unsigned char *b1 = (unsigned char*)&age;

	if (*b1 == 0x12)
		printf("%s", "大端系统");
	else if(*b1 == 0x34)
	{
		printf("%s", "小端系统");
	}
}

///将数字变成大端序列
void convertToCharFromInt_BigEnd(int input, char* buffer)
{
	buffer[0] = input >> 24;
	
	buffer[1] = input >> 16;

	buffer[2] = input >> 8;

	buffer[3] = input;
}

//把字符按照大端解析成数字，即字节0x01 0x02 0x03 0x04四个字节，转为int数字0x01020304,低位字节0x01在数字的高位
void convertToIntFromChar_BigEnd(const char* buffer, int& input)
{
	int a = buffer[0] <<24;

	a |= buffer[1] << 16;

	a |= buffer[2] << 8;

	a |= buffer[3];
	input = a;
}

///将数字变成小端序列
void convertToCharFromInt_LittleEnd(int input, char* buffer)
{
	buffer[0] = input;

	buffer[1] = input >> 8;

	buffer[2] = input >> 16;

	buffer[3] = input >> 24;
}

//把字符按照小端解析成数字，即字节0x01 0x02 0x03 0x04四个字节，转为int数字0x01020304,低位字节0x01在数字的低位
void convertToIntFromChar_LittleEnd(const char* buffer, int& input)
{
	int a = buffer[3] << 24;

	a |= buffer[2] << 16;

	a |= buffer[1] << 8;

	a |= buffer[0];
	input = a;
}


int main()
{
	char buffer[4];
	convertToCharFromInt_BigEnd(0x01020304, buffer);
	int value;
	convertToIntFromChar_BigEnd(buffer, value);

	convertToCharFromInt_LittleEnd(0x01020304, buffer);
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

