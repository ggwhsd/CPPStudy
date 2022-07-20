#pragma once

#include "cmdline.h"
#include <string>
using namespace std;

void parserOne(int argc, char* argv[])
{
	cmdline::parser a;
	a.add<string>("host",'h',"host name",true,"");
	a.add<int>("port", 'p', "port number", false, 80, cmdline::range(1, 65535));
	a.add<string>("type", 't', "protocol type", false, "http", cmdline::oneof<string>("http", "https", "ssh", "ftp"));

	a.add("gzip", '\0', "gzip when transfer");
	a.parse_check(argc, argv);
	cout << a.get<string>("type") << "://"
		<< a.get<string>("host") << ":"
		<< a.get<int>("port") << endl;

	if (a.exist("gzip")) cout << "gzip" << endl;
}

/// <summary>
/// ���Ӿ�ϸ��ʹ��cmdline
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void parserMore(int argc, char* argv[])
{
	cmdline::parser a;
	a.add<string>("host", 'h', "host name", true, "");
	a.add<int>("port", 'p', "port number", false, 80, cmdline::range(1, 65535));
	a.add<string>("type", 't', "protocol type", false, "http", cmdline::oneof<string>("http", "https", "ssh", "ftp"));
	a.add("help", 0, "print this message");

	//���Ӷ�����ʾ��Ϣ
	a.footer("filename ...");
	a.set_program_name("test");
	//ͨ��parse��������ʾ��1��ͬ
	bool ok = a.parse(argc, argv);
	if (argc == 1 || a.exist("help"))
	{
		cerr << a.usage();
		return ;
	}
	if (!ok) 
	{
		cerr << a.error() << endl << a.usage();
		return;
	}
	
	cout << a.get<string>("host") << ":" << a.get<int>("port") << endl;

	for (size_t i = 0; i < a.rest().size(); i++)
	{
		cout << "- " << a.rest()[i] << endl;
	}
	return;

}