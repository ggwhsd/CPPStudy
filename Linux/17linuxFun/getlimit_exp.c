#include <stdio.h>
#include <stdlib.h>

#include <sys/resource.h>

int main()
{
        rlimit rl;
        getrlimit(RLIMIT_CPU,&rl);
        printf("CPU : sys %d, current %d\n", rl.rlim_max, rl.rlim_cur);
        
        getrlimit(RLIMIT_FSIZE,&rl);
        printf("FSIZE : sys %d, current %d\n", rl.rlim_max, rl.rlim_cur);
        
        getrlimit(RLIMIT_DATA,&rl);
        printf("DATA : sys %d, current %d\n", rl.rlim_max, rl.rlim_cur);
        
        getrlimit(RLIMIT_STACK,&rl);
        printf("STACK : sys %d, current %d\n", rl.rlim_max, rl.rlim_cur);
        
        getrlimit(RLIMIT_CORE,&rl);
        printf("CORE : sys %d, current %d\n", rl.rlim_max, rl.rlim_cur);
        
        
        return 0;
}