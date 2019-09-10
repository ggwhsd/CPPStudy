#include <stdio.h>
#include <stdlib.h>

static char buff[256];
static char* string;
int main()
{
   printf("please input a  string:");
   gets(string);
   printf("your string is %s\n",string);
   return 0;
}
