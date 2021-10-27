#include <stdio.h>
#include <time.h>
#include <string.h>

//c++11中的chrono里面有对于时间的新的设计，如下是传统c语言中的使用。
int main()
{
    time_t timep;
    time(&timep);  //获取时间，单位为秒,存入time_t的结构
    printf("ctime return:%s", ctime(&timep));   //ctime负责转换time_t到char*
    
    time_t timep1, timep2;
    time(&timep1);
    time(&timep2);
    printf("%s", asctime(gmtime(&timep1)));  //gmtime是负责将time_t转换为更为结构化的tm结构，返回基于UTC的时间, 
    printf("%s", asctime(localtime(&timep1)));  //返回基于本地时区的时间
    
    char buff[128];
    memset(buff, '\0', 128);
    printf("global time:");
    strftime(buff,128,"%z",gmtime(&timep1));  //strftime可以只获取时间中的某个字段为字符串
    printf("Time Zone:%s\n",buff);
    
    printf("local time:");
    strftime(buff,128,"%z",localtime(&timep1));  //strftime可以只获取时间中的某个字段为字符串
    printf("Time Zone:%s\n",buff);
    return 0;
}