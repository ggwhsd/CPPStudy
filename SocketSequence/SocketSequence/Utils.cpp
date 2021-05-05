#include "Utils.h"
#include <string>
#include <chrono>
#include <time.h>

void IsLitten()
{
	unsigned short age = 0x1234;
	unsigned char *b1 = (unsigned char*)&age;

	if (*b1 == 0x12)
		printf("%s", "���ϵͳ");
	else if (*b1 == 0x34)
	{
		printf("%s", "С��ϵͳ");
	}
}

///�����ֱ�ɴ������
void convertToCharFromInt_BigEnd(int input, char* buffer)
{
	buffer[0] = input >> 24;
	buffer[1] = input >> 16;
	buffer[2] = input >> 8;
	buffer[3] = input;
}

//���ַ����մ�˽��������֣����ֽ�0x01 0x02 0x03 0x04�ĸ��ֽڣ�תΪint����0x01020304,��λ�ֽ�0x01�����ֵĸ�λ
void convertToIntFromChar_BigEnd(const char* buffer, int& input)
{
	int a = buffer[0]  << 24 & (0xff000000);
	a |= buffer[1]  << 16 & (0x00ff0000);
	a |= buffer[2]  << 8 & (0x0000ff00);
	a |= buffer[3] & (0x000000ff);
	input = a;
}

///�����ֱ��С������
void convertToCharFromInt_LittleEnd(int input, char* buffer)
{
	buffer[0] = input;
	buffer[1] = input >> 8;
	buffer[2] = input >> 16;
	buffer[3] = input >> 24;
}

//���ַ�����С�˽��������֣����ֽ�0x01 0x02 0x03 0x04�ĸ��ֽڣ�תΪint����0x01020304,��λ�ֽ�0x01�����ֵĵ�λ
void convertToIntFromChar_LittleEnd(const char* buffer, int& input)
{
	/*
	int a = 0;
	memcpy(&a, buffer, 4);
	input =a;
	*/
	//��ΪcharΪ�з���λ�����ֱ��ת��int������0x80��ת��Ϊ0xffffff80����˶�Ҫ�����ֽ������㡣
	int a = buffer[3] << 24 & 0xff000000;
	a |= buffer[2] << 16 & 0x00ff0000;
	a |= buffer[1] << 8 & 0x0000ff00;
	a |= buffer[0] & 0x000000ff;
	input = a;
}



std::string getNow()
{
	char timebuf[30] = { 0 };
	auto tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
	time_t now = std::chrono::system_clock::to_time_t(tp);
	tm *ltm = localtime(&now);
	strftime(timebuf, 30, "%F %R:%S", ltm);
	char mircostr[9];
	mircostr[7] = ' ';
	mircostr[8] = '\0';
	sprintf_s(mircostr, ".%06d", (int)(tp.time_since_epoch().count() % (1000000)));
	strcat_s(timebuf, mircostr);
	return std::string(timebuf);
}