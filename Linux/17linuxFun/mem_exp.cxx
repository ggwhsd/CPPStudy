#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_memcpy()
{
   char *p1 = "abcdefghijklm";
   char *p2 = (char*) malloc(10*sizeof(char));
   char *p3 = (char*) memcpy(p2,p1,10);
   printf("p1=%s p2=%s p3=%s p1:%x p2:%x p3:%p\n", p1, p2, p3, p1, p2, p3);
   free(p2);
   
}



void test_memmove()
{
   char *p1 = "abcdefghijklm";
   char *p2 = (char*) malloc(10*sizeof(char));
   char *p3 = (char*) memmove(p2,p1,10);
   printf("p1=%s p2=%s p3=%s p1:%x p2:%x p3:%p\n", p1, p2, p3, p1, p2, p3);
   free(p2);

}


void test_memset()
{
  
      char *p2 = (char*) malloc(10*sizeof(char));
   memset(p2,'\0',10);
   memset(p2,'1',9);
   char *p3=(char*)memchr(p2,'1',5);
   printf("p2=%s  p2:%x p3:%s\n", p2, p2, p3);
   free(p2);


}






int main(void)
{

   test_memcpy();
   test_memmove();
   test_memset();
   return 0;
}
