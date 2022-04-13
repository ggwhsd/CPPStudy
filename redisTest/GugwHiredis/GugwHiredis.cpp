#include "pch.h"
#include "GugwHiredis.h"
#include <hiredis.h>
#include <iostream>

using namespace std;
const int i_len_redisContext=100;
redisContext* p_array_redisContext[i_len_redisContext] = {nullptr};

int getNewRedisContextIndex()
{
	for (int i = 0; i < 100; i++)
	{
		if (p_array_redisContext[i] != nullptr)
		{
			continue;
		}
		else
		{
			return i;
		}
	}
	return -1;
}

int  Gugw::Gugw_redisConnect(const char * ip, int port)
{
	cout << "连接成功"  << endl;
	//redis默认监听端口为6387 可以再配置文件中修改 
	redisContext* pRedisContext = redisConnect(ip, port);
	if (NULL == pRedisContext || pRedisContext->err)
	{
		printf("%s \r\n", pRedisContext->errstr);
		printf("Connect to redis server failed \n");
		return -1;
	}
	else
	{
		cout << "connect successfully" << endl;
		int index = getNewRedisContextIndex();
		p_array_redisContext[index] = pRedisContext;
		return index;
	}
}

Gugw::Gugw_redisReply Gugw::Gugw_redisCommand(int redisContextIndex, const char* const command)
{
	//cout << "执行command " << command << endl;
	redisContext* pRedisContext = p_array_redisContext[redisContextIndex];

	Gugw::Gugw_redisReply reply;
	reply.redisError = -1;
	reply.replayMsg = "";
	if (nullptr == pRedisContext)
		return reply;
	//获取redis的回报
	redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, command);
	if (nullptr == pRedisReply)
	{
		return reply;
	}
	
	//转换为我们客户端的回报
	if (pRedisReply->len > 0)
	{

		reply.replayMsg = pRedisReply->str;
	}
	else
	{
		
	}
	if (pRedisReply->type == REDIS_REPLY_NIL)
		reply.redisError = 4;
	else if (pRedisReply->type == REDIS_REPLY_ERROR)
		reply.redisError = 6;
	else
		reply.redisError = 0;
	
	freeReplyObject(pRedisReply);
	return reply;
}
