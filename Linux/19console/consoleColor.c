#include <stdlib.h>
#include <stdio.h>
#define BCK_WHITE 47
#define BCK_BLACK 40
#define BCK_RED 41
#define BCK_GREEN 42
#define BCK_YELLOWBLUE 43
#define FON_RED 31
#define FON_BLACK 30
#define CONTROL_SHANSHUO \033[5m
#define CONTROL_CLOSE_ALL_SETTING \033[0m
#define CONTROL_UNDERLINE "\033[4m"
#define CONTROL_FANXIAN \033[7m
#define CONTROL_YINCANG \033[8m
#define CONTROL_BASE_FONT \033[10
#define CONTROL_CURSOR_UPMOVE(n) \033[nA
#define CONTROL_CURSOR_BLOWMOVE(n) \033[nB
#define C_C_RIGHTMOVE(n) \033[nC
#define C_C_LEFTMOVE(n) \033[nD
#define CONTROL_CURSOR_SET(x,y) \033[y,xH
#define CONTROL_CLEAR \033[2J
#define CONTROL_CURSOR_SHOW \033[?25h
#define CONTROL_CURSOR_HIDE \033[?25l



int main(int argc, char **argv)
{
   printf("\033[47;31m helloworld \033[5m");
   printf("\r\n");
   printf("\033[%d;%dm helloworld \033[0m\r\n",BCK_WHITE,FON_BLACK);
   printf("\033[4m \033[%d;%dm helloworld \r\n",BCK_RED,FON_BLACK);
   printf("\033[1A \033[?25l hello world");
   
return 0;
}


