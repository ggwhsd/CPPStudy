#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void catch_sigalrm(int signo)
{
	;
}

unsigned int mysleep(unsigned int second)
{
	struct sigaction act,oldact;
act.sa_handler= catch_sigalrm;
sigemptyset(&act.sa_mask);
act.sa_flags=0;

sigaction(SIGALRM, &act, &oldact);
alarm(second);
int ret =pause();
if(ret==-1 )
{
printf("pause success\n");
}
alarm(0);
sigaction(SIGALRM, &oldact,NULL);
return ret;
}

int main(void)
{
mysleep(3);
}

