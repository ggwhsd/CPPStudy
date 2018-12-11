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


/*
{
"pi": 3.141,
"happy" : true,
"name" : "Niels",
"nothing" : null,
"answer" : {
"everything": 42
},
"list" : [1, 0, 2],
"object" : {
"currency": "USD",
"value" : 42.99
}
}

*/
void JsonCreateMethod1()
{
	json j;
	j["pi"] = 3.141;
	j["happy"] = true;
	j["name"] = "Niels";
	j["nothing"] = nullptr;
	j["answer"]["everything"] = 42;
	j["list"] = { 1,2,3 };
	j["object"] = { {"currency","USD"},{"value",42.99} };


}
void JsonCreateMethod2()
{

	json j2 = {
		{ "pi", 3.141 },
		{ "happy" , true },
		{ "name" , "Niels" },
		{ "nothing",nullptr },
		{ "answer",{
					{ "everything",42 }
					},
		{ "list" ,{ 1, 0, 2 } },
		{ "object" ,{
					{ "currency", "USD" },
					{ "value",42.99 }
					}
		}
		}
	};
}

void JsonCreateMethod3()
{
	// a way to express the empty array []
	json empty_array_explicit = json::array();

	// ways to express the empty object {}
	json empty_object_implicit = json({});
	json empty_object_explicit = json::object();

	// a way to express an _array_ of key/value pairs [["currency", "USD"], ["value", 42.99]]
	json array_not_object = json::array({ { "currency", "USD" },{ "value", 42.99 } });
}

void SerializationMethod1()
{
	// create object from string literal
	json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

	// or even nicer with a raw string literal
	auto j2 = R"(
  {
    "happy": true,
    "pi": 3.141
  }
)"_json;
}