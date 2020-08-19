#pragma once
#include <string.h>
#include <iostream>



void writelog(const char* msg)
{
	std::cout << msg << std::endl;
}

void inivite_fun(const char* msg)
{
	writelog(msg);
}
void tring_fun(const char* msg)
{
	writelog(msg);
}
void ring_181_fun(const char* msg)
{
	writelog(msg);
}

void msg_proc(const char * msg_type, const char * msg_buf)
{
	if (0 == strcmp(msg_type, "inivite"))
	{
		inivite_fun(msg_buf);
	}
	else if (0 == strcmp(msg_type, "tring_100"))
	{
		tring_fun(msg_buf);
	}
	else if (0 == strcmp(msg_type, "tring_180"))
	{
		ring_181_fun(msg_buf);
	}
	else
	{
		writelog("没有找到消息类型");
	}
}




typedef void(*FUN)(const char*);
typedef struct __msg_fun_st
{
	const char* msg_type; //消息类型，如果需要更复杂的表驱动，可以扩展这个字段为struct
	FUN fun_ptr;
}msg_fun_st;
msg_fun_st msg_flow[] =
{
	{"inivite",inivite_fun},
	{"tring_100",tring_fun},
	{"ring_181",ring_181_fun}
};
void msg_proc_st(const char * msg_type, const char * msg_buf)
{
	int type_num = sizeof(msg_flow) / sizeof(msg_fun_st);
	int i = 0;
	for (i = 0; i < type_num
		; i++)
	{
		if (0 == strcmp(msg_flow[i].msg_type, msg_type))
		{
			msg_flow[i].fun_ptr(msg_buf);
			return;
		}
	}
	writelog("没有找到消息类型");
}