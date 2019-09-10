#include <stdio.h>
int main(int argc, char** argv)
{
   FILE*fp =NULL;
   char str[10];
   if((fp=fopen("aa.txt","r"))==NULL)
   {
      printf("can not open file\n");
      return -1;
   }
   fgets(str,sizeof(str),fp);
   fputs(str,stdout);
   fclose(fp);
   return 0;
}
