#pragma once
#include <stdio.h>
#include <string>

void IsLitten();

///�����ֱ�ɴ������
void convertToCharFromInt_BigEnd(int input, char* buffer);

//���ַ����մ�˽��������֣����ֽ�0x01 0x02 0x03 0x04�ĸ��ֽڣ�תΪint����0x01020304,��λ�ֽ�0x01�����ֵĸ�λ
void convertToIntFromChar_BigEnd(const char* buffer, int& input);

///�����ֱ��С������
void convertToCharFromInt_LittleEnd(int input, char* buffer);

//���ַ�����С�˽��������֣����ֽ�0x01 0x02 0x03 0x04�ĸ��ֽڣ�תΪint����0x01020304,��λ�ֽ�0x01�����ֵĵ�λ
void convertToIntFromChar_LittleEnd(const char* buffer, int& input);

std::string getNow();