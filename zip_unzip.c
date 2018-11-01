#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zip(int format)
{
	char cmd1[50]="gzip ";
	char cmd2[50]="tar -cf ";
	char file[50];
	switch(format)
	{
		case 1:
			printf("请输入你要压缩的文件名，多个文件以空格间隔");
			getchar();
			fgets(file,50,stdin);
			strcat(cmd1,file);
			system(cmd1);
			printf("你所需要的文件已经成功压缩i\n");
			break;
		case 2:
			printf("你需要的文件名 然后空格输入要归档的文件名，多个文件以空格间隔");
			getchar();
			fgets(file,50,stdin);
			strcat(cmd2,file);
			system(cmd2);
			printf("你所需要的文件已经成功压缩");
			break;
		default:
			printf("你的选择有误，请重新运行该程序");
			exit(0);
	}


}


void unzip(char filename[])
{
	int len;
	char cmd1[50]="gunzip ";
	char cmd2[50]="tar -xvf";
	len=strlen(filename);
	if(filename[len-1]=='z'&&filename[len-2]=='g')
	{
		strcat(cmd1,filename);
		system(cmd1);
		printf("文件已经解压缩\n");
	}
	else if(filename[len-1]=='r'&&filename[len-2]=='a'&&filename[len-3]=='t')
	{
		strcat(cmd2,filename);
		system(cmd2);
		printf("文件已经解压缩\n");
	}
}
	int main()
	{
		int choice;
		int format;
		char filename[30];
		printf("-------------------------------------");
		printf("欢迎使用此压缩解压程序\n");
		printf("1:压缩；\n2解压缩\n");
		label:
			scanf("%d",&choice);
			getchar();
			switch(choice)
			{
				case 1:
					printf("选择了压缩，请输入您需要的压缩格式:\n");
					printf("1: .gz\t2: .tar\n");
					scanf("%d",&format);
					getchar();
					zip(format);
					break;
				case 2:
					printf("选择了解压缩，请输入需要解压缩的文件名:\n");
					getchar();
					fgets(filename,30,stdin);
					unzip(filename);
					break;
				default:
					printf("您的选择有误，请重新输入\n");
					goto label;


			}
		printf("---------------------------------------");
	    return 0;
	}

