#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *p = getenv("HOSTNAME");
    printf("*p = %s\n", p);
    return 0;
}
