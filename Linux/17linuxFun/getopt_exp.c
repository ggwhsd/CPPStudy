#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//getopt函数，第三个参数指示哪些是要作为命令选项解析的，
//:表示必选可以有空格分隔参数选项和参数值，::表示可选且不能有空格
//getopt只支持a b 这类短的，不支持长的。
//getopt_long支持长参数。

int main(int argc, char **argv, char *envp[])
{
    int result;
    int i =0;
    while(envp[i]!=nullptr)
    {
        printf("%s",envp[i]);
        i++;
    }
    
    printf("\n======================\n");
    
    opterr = 0;
    printf("resolve the argv:\n");
    while((result = getopt(argc, argv, "a:b:c::")) != -1)
    {
        switch(result)
        {
            case 'a':
             printf("option = a, optopt=%c,  optarg=%s\n",optopt, optarg);
            break;
            case 'b':
             printf("option = b, optopt=%c,  optarg=%s\n",optopt, optarg);
            break;
            case 'c':
             printf("option = c, optopt=%c,  optarg=%s\n",optopt, optarg);
            break;
            case '?':
             printf("option = ?, optopt=%c,  optarg=%s\n",optopt, optarg);
            break;
            default:
             printf("default result = %c", result);
            break;
        }
        printf("argv[%d]=%s\n", optind, argv[optind]);
    }
    printf("result=-1, optind=%d\n", optind, argv[optind]);
    printf("unresolve the argv:\n");
    for(result = optind; result < argc; result++)
    {
        printf("----- argv[%d]=%s\n",result, argv[result]);
        
    }
    printf("all the argv:\n");
    for(result = 1; result < argc; result++)
    {
        printf("at the end ----- argv[%d]=%s\n", result, argv[result]);
    }
    return 0;
}