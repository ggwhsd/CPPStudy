#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
/*
	random display a word ，input word ，test it 
*/
int main()
{
   struct timeval tv1,tv2;
   struct timezone tz;
   float tm = 0.0f;
   int repeat = 25,i,crt = 0,k,n;
   
   srand((int)time(0));
   for(int i=0;i<repeat;i++)
   {
		k = (int)(10.0*rand()/(RAND_MAX+1.0));
		printf("%d: %d ---", i+1, k);
		gettimeofday(&tv1, &tz);
		scanf("%d",&n);
		gettimeofday(&tv2, &tz);
		if(n==k)
		{
			crt++;
			tm+=(tv2.tv_sec-tv1.tv_sec)+(tv2.tv_usec-tv1.tv_usec)/1000000.0f;
		}
   }
   tm /= crt*1.0f;
   printf("correstness rate: %d%%\n", (int)(crt * 100.0 / repeat));
   printf("average time taken: %.2f sec(s)\n", tm);
   
	
}
