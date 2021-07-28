#pragma once
#include <string>

namespace Gugw{
	struct Gugw_redisReply
	{
		std::string replayMsg; 
		int redisError; //-1��ʾ����ʧ�ܣ���������ʾ��ȷ��
	};

// ����ֵ��Ϊredis�ı�ţ������ڲ�ȷ��Ψһ��redisʵ������
int Gugw_redisConnect(const char *ip, int port);

// ����ֵ��string
Gugw_redisReply Gugw_redisCommand(int redisContext, const char* const command);


}