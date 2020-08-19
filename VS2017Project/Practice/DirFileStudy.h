#pragma once

#include <iostream>
#include <string>
#include <io.h>
#include <direct.h>
using namespace std;
namespace DirStudy {
	void TestCreateDirOne()
	{
		std::cout << "Hello World!\n";
		string logPath = ".\\Log";
		if (_access(logPath.c_str(), 0) == -1)	//如果文件夹不存在
			_mkdir(logPath.c_str());
		std::cout << "Hello World!\n";
		system("pause");
	}

	int TestCreateDirectorys(std::string path)
	{
		int len = path.length();
		char tmpDirPath[256] = { 0 };
		for (int i = 0; i < len; i++)
		{
			tmpDirPath[i] = path[i];
			if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
			{
				if (_access(tmpDirPath, 0) == -1)
				{
					int ret = _mkdir(tmpDirPath);
					if (ret == -1) return ret;
				}
			}
		}
		return 0;
	}
}