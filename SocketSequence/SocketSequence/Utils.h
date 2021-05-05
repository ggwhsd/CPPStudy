#pragma once
#include <stdio.h>
#include <string>

void IsLitten();

///将数字变成大端序列
void convertToCharFromInt_BigEnd(int input, char* buffer);

//把字符按照大端解析成数字，即字节0x01 0x02 0x03 0x04四个字节，转为int数字0x01020304,低位字节0x01在数字的高位
void convertToIntFromChar_BigEnd(const char* buffer, int& input);

///将数字变成小端序列
void convertToCharFromInt_LittleEnd(int input, char* buffer);

//把字符按照小端解析成数字，即字节0x01 0x02 0x03 0x04四个字节，转为int数字0x01020304,低位字节0x01在数字的低位
void convertToIntFromChar_LittleEnd(const char* buffer, int& input);

std::string getNow();