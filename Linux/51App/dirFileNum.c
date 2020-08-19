#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int getFileNum(char* root)
{
	//open dir
	DIR* dir = NULL;
	dir = opendir(root);
	if(dir == NULL)
	{
		perror("opendir");
		exit(1);
	}
	//travel dir
	struct dirent *ptr_info=NULL;
	char path[1024]={0};
	int num=0;
	while( ( ptr_info = readdir(dir)) != NULL)
	{
		if(strcmp(ptr_info->d_name, ".")==0 || strcmp(ptr_info->d_name,"..")==0)
			continue;
		if(ptr_info->d_type == DT_DIR)
		{
			sprintf(path,"%s/%s",root,ptr_info->d_name);
			num += getFileNum(path);
		}
		if(ptr_info->d_type == DT_REG)
		{
			num +=1;
		}
	}
	closedir(dir);
	return num;
}

int main(int argc , char * argv[1])
{

	int Num = getFileNum(argv[1]);
	printf("Num %d\n",Num);
	return 0;
}
