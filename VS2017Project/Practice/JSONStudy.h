#pragma once
#include "NLOHMANN_JSON.h"
#include <iostream>
using namespace std;

using json = nlohmann::json;
void testJsonRead()
{
	while (true)
	{
		json j;  //����json��
		cin >> j;   //��cin����json����
		cout << j;  //������л���json
	}

}