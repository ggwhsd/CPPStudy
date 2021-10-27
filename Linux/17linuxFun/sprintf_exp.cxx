#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//将数字变成字符串 ，多数情况可以代替itoa使用
int main()
{
    srand(time(0));
    char s[64];
    int offset  = 0;
    int i ;
    for(i = 0; i <10; i++)
    {
        offset += sprintf(s+offset,"%d", rand()%100);
    }
    s[offset-1]='\n';
    printf(s);
    

    return 0;
    
}