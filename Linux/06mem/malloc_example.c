#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[], char* envp[])
{
   int count;
   int* array;
   if((array=(int*)malloc(10*sizeof(int)))==NULL)
   {
       printf("malloc memeory unsuccessful");
       exit(1);
   }
   for(count=0;count<10;count++)
   {
      printf("%4d",*array);
      *array=count;
      array++;
   }
   for(count=9;count>=0;count--)
   {
      array--;
      printf("%4d",*array);
   }
   printf("\n");
   free(array);
   array=NULL;
   exit(0);
   
}
