#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#define N 3

int LEN=10000;
void InsertionSort(long input[], int len)
{
   int i,j,temp;
   for(i=1; i<len; i++)
   {
      temp = input[i];
	  for(j=i-1;j>-1&& input[j]>temp; j--)
	  {
	     input[j+1] = input[j];
		 input[j] = temp;
	  }
   }
}

void ShellSort(long v[], int n)
{
   int gap,i,j,temp;
   for(gap=n/2;gap>0;gap/=2)
   {
      for(i=gap;i<n;i++)
	  {
	     for(j=i-gap;(j>=0) && (v[j]>v[j+gap]);j -= gap)
		 {
		    temp=v[j];
			v[j]=v[j+gap];
			v[j+gap]=temp;
		 }
	  }
   }
}

void HalfInsertSort(long a[], int len)
{
   int i, j, temp;
   int low, high, mid;
   for(i=1; i<len; i++)
   {
      temp = a[i];
	  low=0;
	  high=i-1;
	  while(low<=high)
	  {
	     mid=(low+high)/2;
		 if(a[mid]>temp)
		 	high=mid-1;
		 else
		 	low=mid+1;
	  }
	  for(j=i-1;j>high;j--)
	  {
	     a[j+1]=a[j];
	  }
	  a[high+1]=temp;
   }
}

double test(void (*fp)(long a[], int len))
{
   long a[LEN];
   double b;
   int i,j;
   struct timeval tv1,tv2;
   struct timezone tz;
   j = (int)time(0);
   srand(j);
   for(i=0;i<LEN;i++)
   {
   		a[i]=rand();
		srand(++j);
   }
   gettimeofday(&tv1, &tz);
   (*fp)(a,LEN);
   gettimeofday(&tv2, &tz);
   b = (tv2.tv_sec - tv1.tv_sec)+(tv2.tv_usec - tv1.tv_usec)/1000000.0;
   return b;
}

int main()
{
   printf("input sort numbers:\n");
   scanf("%d",&LEN);
   printf(" insertion sort: %8f\n",test(InsertionSort));
   printf(" half insertion sort:%8f\n",test(HalfInsertSort));
   printf(" shell sort:%8f\n",test(ShellSort));
   return 0;
}
