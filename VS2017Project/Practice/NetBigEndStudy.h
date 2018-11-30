#pragma once
#include <iostream>
#include <string>
/*
 * 0x12345678   16���ƣ�����������һ�ֽ�,12 34 56 78 �����ĸ��ֽڡ�
 *      �����ַ 00 01 02 03
 * ��˴洢��ʽ: 12 34 56 78
 * С�˴洢��ʽ: 78 56 43 21
 * һ����Զ���С�ˣ��������紫�䶼��Ҫ���˴��䣬������Ҫת��
 * ����ʹ��htonl�Ⱥ�������ת������С��ת����ˣ�Ҳ�����Լ�д������
 * ���Ҫת�����ַ������飬����Ҫ�Լ�д
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
	//��˴洢��ʽ
	toBigByte(a, buf);
	//��ʵֵ
	unsigned int b = fromBigBytes(buf);
	
	
	unsigned short d =htons(a);

	//С�˴洢��ʽ
	toSmallByte(a,buf);
	//��ʵֵ
	b = fromSmallBytes(buf);
	


}