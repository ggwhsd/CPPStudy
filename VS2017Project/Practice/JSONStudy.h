#pragma once
#include "NLOHMANN_JSON.h"
#include <iostream>
#include <fstream>
using namespace std;

using json = nlohmann::json;

//https://github.com/nlohmann/json
namespace JSONSTUDY {
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
		//j.push_back(j);
		cout << j.dump() << endl;;

		//cout << j["pi"] << endl;


		json::iterator it = j.begin();
		cout << it.key() << " " << it.value() << endl;

	
		if (j["dd"] == NULL)
			cout << "NULL" << endl;
		if (j["dd"] == nullptr)
			cout << "nullptr" << endl;

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
		//j2.push_back(j2);
		cout<<j2.dump();
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

	void FromStringTOJsonObject()
	{
		// create object from string literal, 
		// if without _json, the stringliteral is not parsed to object. 
		json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
		json j1 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
		// or even nicer with a raw string literal
		auto j2 = R"(
					  {
						"happy": true,
						"pi": 3.141
					  }
					)"_json;
	}

	void stringSerialized()
	{
		json j = "this is a string";
		// explicit conversion to string
		std::string s = j.dump();    // {\"happy\":true,\"pi\":3.141}
		std::cout << j.dump(4) << std::endl;

		std::string cpp_string2;
		j.get_to(cpp_string2);
		//assignmen 
		auto cpp_string = j.get<std::string>();

		cout <<"j.dump="<< s << endl;
		cout << "j.get_to()=" << cpp_string2 << endl;
		cout << "j.get()=" << cpp_string << endl;
	}

	void fileDeserialize()
	{
		// read a JSON file
		std::ifstream i("file.json");
		json j;
		i >> j;

		// write prettified JSON to another file
		std::ofstream o("pretty.json");
		o << std::setw(4) << j << std::endl;
	}

	void iteratorRead()
	{
		json j2 = {
			{ "pi", 3.141 },
		{ "happy" , true },
		{ "name" , "Niels" },
		{ "nothing","nothing" },
		{ "list" ,{ 1, 0, 2 } }
		};
		

		for (json::iterator it = j2.begin(); it != j2.end(); ++it) {
			std::cout << it.key() << " : " << it.value() << "\n";
		}
	}



}