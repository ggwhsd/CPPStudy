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


//��ȡ����·��
string testShowExecDirectory()
{
	char path[1000];
	GetModuleFileNameA(NULL, path, MAX_PATH);        //��ȡ������·����
	cout << " FullPath=" << path << endl;
	*strrchr(path, '\\') = '\0';                     //��ȡ·��

	cout << " Path=" << path << endl;
	string spath = "";
	spath.append(path);

	return spath;
}

//�ڳ���·���£�����logĿ¼
void testCreateDirectory()
{
	char DirName[] = "log";
	string Home = testShowExecDirectory();
	cout << " Home=" << Home.c_str() << endl;
	Home.append("\\");
	Home.append(DirName);
	cout << " Home=" << Home.c_str() << endl;
	getchar();
	_mkdir(Home.c_str());//������Ǵ���һ��Ŀ¼ mkdir ����make directory ����˼
	getchar();
	_rmdir(Home.c_str());
	
	
}




void getFiles(string path, vector<string>& files) {
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;

	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*.*").c_str(), &fileinfo)) != -1) {

		do {
			//�����Ŀ¼,����֮
			//�������,�����б�
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
	��ȡ��ǰ����Ŀ¼���ڿ����������棬���ǳ�������Ŀ¼�����ǹ�������Ŀ¼��
	����release�汾�ĳ����£����ǳ�������Ŀ¼.
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

