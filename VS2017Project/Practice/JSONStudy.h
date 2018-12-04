#pragma once
#include "NLOHMANN_JSON.h"
#include <iostream>
using namespace std;

using json = nlohmann::json;
void testJsonRead()
{
	while (true)
	{
		json j;  //创建json类
		cin >> j;   //从cin读入json对象
		cout << j;  //输出序列化的json
	}

}