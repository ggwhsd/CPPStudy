#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int main()
{
   double a,b;
   printf("请输入自变量:");
   scanf("%lf",&a);
   b=sin(a);
   printf("sin(%lf)=%lf\n",a,b);
   srand((unsigned)time(0));
   int test = 0;
   test = rand()%100 + 1;
   printf("rand is %d\n",test);



   return 0;
}
