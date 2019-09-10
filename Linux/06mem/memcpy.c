#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
   char *p1="abcdefg";
   char *p2=(char *)malloc(10*sizeof(char));
   char *p3=memcpy(p2,p1,10);
   printf("*p3=%s,*p2=%s",p3,p2);
   free(p2);
   return 0;
}
