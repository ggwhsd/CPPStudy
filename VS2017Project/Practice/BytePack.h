#pragma once
#include <string.h>
#include <iostream>

using namespace std;

#pragma pack(push,2)  //���浱ǰ���䷽ʽ��ջ��Ȼ��ʹ��2�ֽ�Ϊ��ǰ���䷽ʽ
struct samplePlainObject
{
    char a;       //1���ֽڣ�������8���ֽڣ�����1�ֽڶ���Ϊ        2�ֽڡ�
    double b;        // 8�ֽڣ��Ѷ���2�ֽ�
    unsigned char c : 1;    // 1 ����
    unsigned char c1 : 1;   // 1 ����
    unsigned char c2 : 1;   // 1 ����
    unsigned char c3 : 1;   // 1 ���أ� ����4������ռ��1���ֽڣ�����intΪ4�ֽڣ����Զ��뷽ʽ���Ϊ   2�ֽ�
    int d;      //4�ֽڣ��Ѿ�����2�ֽڡ�   ����һ��  2+ 8+ 2+ 4 = 16�ֽ�
};
#pragma pack(pop) //��ջ֮ǰ����Ķ��䷽ʽΪ��ǰ���뷽ʽ
#pragma pack()  //�ָ�Ĭ�϶��䷽ʽ
void TestPragmaPack()
{
    samplePlainObject s1;
    memset(&s1, 0, sizeof(s1));
    s1.a = 'a';
    s1.b = 1;
    s1.c = true;
    s1.c1 = true;
    s1.c2 = true;
    int len = sizeof(s1);
    cout << len << endl;              //16
    cout << sizeof(char) << endl;    //1
    cout << sizeof(double) << endl;   //8
    cout << sizeof(int) << endl;      //4
    char buff[255];

    memcpy(buff, &s1, len);
    for (int i = 0; i < len; i++)
        cout << std::hex << (int)buff[i] << ",";   //61,0,0,0,0,0,0,0,fffffff0,3f,7,0,0,0,0,0,
    samplePlainObject* s2 = (samplePlainObject*)(buff);    //ת��֮���s2�е����ݺ�s1һ����
}