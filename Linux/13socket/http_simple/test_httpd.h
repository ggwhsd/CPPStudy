#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>

char ip[128];
char port[128];
char back[128];
char home_dir[128];


