#include <stdio.h>
#include  <string.h>

int main(int argc, char** argv)
{
   int i;
   char a[10];
	printf("input string");
	scanf("%s",a);
	i=printf("the input string is : %s",a);
	printf("the last printf return %d \n",i);
	return 0;
   
}
