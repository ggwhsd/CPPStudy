#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
int main()
{
   double a,b;
   srand((unsigned)time(0));
   int test = 0;
   test = rand()%100 + 1;
   printf("rand is %d\n",test);
   time_t t;
   time(&t);
   printf("%s",asctime(localtime(&t)));
   
   struct timeval tv1,tv2;
   gettimeofday(&tv1,NULL);
   sleep(1);
   mkdir("dir",S_IXUSR);
   gettimeofday(&tv2,NULL);
   printf("t1.sec %ld t2.sec %ld ",tv1.tv_sec,tv2.tv_sec);
   double sec = tv2.tv_sec - tv1.tv_sec ;
   double usec = (tv2.tv_usec - tv1.tv_usec)/1000000;
   double sum = sec + usec;
   printf("seconds are %lf \n",sum);
   

   return 0;
}
