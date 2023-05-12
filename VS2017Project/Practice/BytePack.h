#pragma once
#include <string.h>
#include <iostream>

using namespace std;

#pragma pack(push,2)  //保存当前对其方式入栈，然后使用2字节为当前对其方式
struct samplePlainObject
{
    char a;       //1个字节，后面是8个字节，所以1字节对齐为        2字节。
    double b;        // 8字节，已对齐2字节
    unsigned char c : 1;    // 1 比特
    unsigned char c1 : 1;   // 1 比特
    unsigned char c2 : 1;   // 1 比特
    unsigned char c3 : 1;   // 1 比特， 至此4个比特占用1个字节，后面int为4字节，所以对齐方式结果为   2字节
    int d;      //4字节，已经对齐2字节。   至此一共  2+ 8+ 2+ 4 = 16字节
};
#pragma pack(pop) //出栈之前保存的对其方式为当前对齐方式
#pragma pack()  //恢复默认对其方式
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
    samplePlainObject* s2 = (samplePlainObject*)(buff);    //转换之后的s2中的内容和s1一样。
}