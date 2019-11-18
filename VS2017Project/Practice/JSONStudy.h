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
		std::string s = j.dump();  
		std::cout << j.dump(2) << std::endl;

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


	//自定义结构，需要重载如下函数方法进行序列化和反序列化

	namespace nlohmann {
		struct Person {
			string name;
			int age;
		};

		struct Persons
		{
			vector<Person> persons;
		};

		 void to_json(json& j, const Person& p) {
				j = json{ {"name",p.name},{"age",p.age} };   //设置 结构中的字段与json中的key对照关系，name和age可以随意改成我们想映射的名字，最终显示到json字符串里面。
			}

		 void from_json(const json& j, Person& p) {
				p.name = j.at("name").get<string>();
				p.age = j.at("age").get<int>();
			}
		 void to_json(json& j, const Persons& ps) {
			 j = json{ { "persons", ps.persons } };
		 }
		 void from_json(const json& j, Persons& ps) {
			 ps.persons = j.at("persons").get<vector<Person>>();
		 }

	}
	int  TestObjectToSerial()
	{
		string jsonString = R"(
    {
      "name" : "Joe",
      "age" : 12
    }
)";
		using namespace nlohmann;
		json j = json::parse(jsonString);
		Person p = j;
		
		cout << "name: " << p.name << endl
			<< "age: " << p.age << endl;
		j = p;
		cout << j << endl;
		cout << j.dump(3) << endl;

		return 0;
	}

	int TestObjectToSerial2()
	{
		string jsonString = R"({
  "persons" : [
    {
      "name" : "Joe",
      "age" : 12
    },
{
      "name" : "Joe2",
      "age" : 122
    }
  ]
})";
		using namespace nlohmann;
		json j = json::parse(jsonString);
		Persons ps = j;
		auto &p = ps.persons[0];
		cout << "name: " << p.name << endl
			<< "age: " << p.age << endl;
		auto &p2 = ps.persons[1];
		cout << "name: " << p2.name << endl
			<< "age: " << p2.age << endl;
		j = ps;
		cout << j << endl;
		cout << j.dump(2) << endl;

		return 0;

	}


	struct Person2 {
		string name;
		int age;
	};
	void to_json(json& j, const Person2& p) {
		j = json{ { "name",p.name },{ "age",p.age } };   //设置 结构中的字段与json中的key对照关系，name和age可以随意改成我们想映射的名字，最终显示到json字符串里面。
	}

	void from_json(const json& j, Person2& p) {
		p.name = j.at("name").get<string>();
		p.age = j.at("age").get<int>();
	}
	int  TestObjectToSeria3()
	{
		string jsonString = R"(
    {
      "name" : "Joe",
      "age" : 12
    }
)";
		//using namespace nlohmann;
		json j = json::parse(jsonString);
		Person2 p = j;

		cout << "name: " << p.name << endl
			<< "age: " << p.age << endl;
		j = p;
		cout << j << endl;
		cout << j.dump(3) << endl;

		return 0;
	}



}