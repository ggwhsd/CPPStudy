#pragma once
#include "./libxml/tinyxml2.h"
#include <iostream>
#include <string>
using namespace std;
using namespace tinyxml2;

void xmlRead()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(".\\testResource\\test.xml");
	const char* content = doc.FirstChildElement("Hello")->GetText();
	printf("Hello,%s", content);
}


void xmlRead2()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(".\\testResource\\test2.xml");
	XMLElement *scene = doc.RootElement();
	XMLElement *surface = scene->FirstChildElement("node");
	while (surface)
	{
		XMLElement *surfaceChild = surface->FirstChildElement();
		const char* content;
		const XMLAttribute *attributeOfSurface = surface->FirstAttribute();
		cout << attributeOfSurface->Name() << ":" << attributeOfSurface->Value() << endl;
		while (surfaceChild)
		{
			content = surfaceChild->GetText();
			string name = surfaceChild->Name();
			surfaceChild = surfaceChild->NextSiblingElement();
			cout << name << " " << content << endl;
		}
		surface = surface->NextSiblingElement();
	}
}


void xmlReadWrite3()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(".\\testResource\\test3.xml");
	XMLElement *scene = doc.RootElement();
	XMLElement *surface = scene->FirstChildElement("node");
	while (surface)
	{
		XMLElement *surfaceChild = surface->FirstChildElement();
		const char* content;
		const XMLAttribute *attributeOfSurface = surface->FirstAttribute();
		cout << attributeOfSurface->Name() << ":" << attributeOfSurface->Value() << endl;
		while (surfaceChild)
		{
			content = surfaceChild->GetText();
			surfaceChild->SetText("xxx");
			surfaceChild = surfaceChild->NextSiblingElement();
			cout << content << endl;
		}
		surface = surface->NextSiblingElement();
	}
	doc.SaveFile(".\\testResource\\test3.xml");
}

void xmlReadWrite4()
{
	tinyxml2::XMLDocument doc;
	const char* declaretion = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	doc.Parse(declaretion);
	tinyxml2::XMLElement * pFirst = doc.NewElement("root");
	doc.InsertEndChild(pFirst);


	tinyxml2::XMLElement *pSecond = doc.NewElement("cmaeraII");
	pSecond->SetText("aaa");
	pSecond->SetAttribute("ss", 1);
	pSecond->SetAttribute("ss1", 1);
	pFirst->InsertEndChild(pSecond);

	doc.SaveFile(".\\testResource\\test4.xml");

}