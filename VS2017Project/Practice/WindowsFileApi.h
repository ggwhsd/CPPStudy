#pragma once
#include <direct.h>
#include <stdlib.h>

#include   <io.h>  
#include   <string>  
#include   <iomanip> 
#include   <vector>
#include   <ctime>  
#include <iostream> 
using namespace std;


//获取程序路径
string testShowExecDirectory()
{
	char path[1000];
	GetModuleFileNameA(NULL, path, MAX_PATH);        //获取到完整路径如
	cout << " FullPath=" << path << endl;
	*strrchr(path, '\\') = '\0';                     //截取路径

	cout << " Path=" << path << endl;
	string spath = "";
	spath.append(path);

	return spath;
}

//在程序路径下，创建log目录
void testCreateDirectory()
{
	char DirName[] = "log";
	string Home = testShowExecDirectory();
	cout << " Home=" << Home.c_str() << endl;
	Home.append("\\");
	Home.append(DirName);
	cout << " Home=" << Home.c_str() << endl;
	getchar();
	_mkdir(Home.c_str());//这个就是创建一个目录 mkdir 就是make directory 的意思
	getchar();
	_rmdir(Home.c_str());
	
	
}




void getFiles(string path, vector<string>& files) {
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;

	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*.*").c_str(), &fileinfo)) != -1) {

		do {
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib   &   _A_SUBDIR)) {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("/").append(fileinfo.name), files);
			}
			else {
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}


/*
	获取当前工作目录，在开发环境里面，不是程序所在目录，而是工程所在目录。
	若在release版本的程序下，则是程序所在目录.
*/
void testShowCurrentDir()
{
	vector<string>   files;

	getFiles(testShowExecDirectory(), files);

	// print the files get
	for (int j = 0; j<files.size(); ++j) {
		cout << files[j] << endl;
	}

}

