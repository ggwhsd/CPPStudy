#pragma once
#include <string>

namespace Gugw{
	struct Gugw_redisReply
	{
		std::string replayMsg; 
		/*
		//  -1 表示返回失败，
		//   0 表示正确
		//   4 表示返回值为空。

		*/
		int redisError; 
	};

// 返回值作为redis的编号，用以内部确定唯一的redis实例连接
int Gugw_redisConnect(const char *ip, int port);

// 返回值是string
Gugw_redisReply Gugw_redisCommand(int redisContext, const char* const command);


}