#pragma once
#include <iostream>
#include <string>
/*
 * 0x12345678   16进制，两个数就是一字节,12 34 56 78 这是四个字节。
 *      假设地址 00 01 02 03
 * 大端存储方式: 12 34 56 78
 * 小端存储方式: 78 56 43 21
 * 一般电脑都是小端，但是网络传输都是要求大端传输，所以需要转换
 * 可以使用htonl等函数进行转换，从小端转到大端，也可以自己写函数。
 * 如果要转换成字符串数组，则需要自己写
 *
 */
using namespace std;

int toBigByte(unsigned int a, unsigned char *buf)
{
	buf[0] = a >> 24;
	buf[1] = a >> 16;
	buf[2] = a >> 8;
	buf[3] = a;
	return 4;
}

unsigned int fromBigBytes(const unsigned char *buf)
{
	unsigned int result = 0;
	result += buf[0] << 24;
	result += buf[1] << 16;
	result += buf[2] << 8;
	result += buf[3];
	return result;
}


int toSmallByte(unsigned int a, unsigned char *buf)
{
	buf[3] = a >> 24;
	buf[2] = a >> 16;
	buf[1] = a >> 8;
	buf[0] = a;
	return 4;
}
unsigned int fromSmallBytes(const unsigned char *buf)
{
	unsigned int result = 0;
	result += buf[3] << 24;
	result += buf[2] << 16;
	result += buf[1] << 8;
	result += buf[0];
	return result;
}

void testBigEnd()
{
	unsigned int a = 0x12345678;
	unsigned char buf[4];
	//大端存储方式
	toBigByte(a, buf);
	//真实值
	unsigned int b = fromBigBytes(buf);
	
	
	unsigned short d =htons(a);

	//小端存储方式
	toSmallByte(a,buf);
	//真实值
	b = fromSmallBytes(buf);
	


}