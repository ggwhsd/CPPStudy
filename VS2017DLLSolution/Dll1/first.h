#pragma once
//û��ʹ��ģ�鶨���ļ�����dll
//__declspec(dllexport) void show(void);
//__declspec(dllexport) int panny(int i, int(*call_back)(int a, int b));
__declspec(dllexport) void showStrIn_Blue(char *);
__declspec(dllexport) void showStrIn_Red_Yello(char *);
__declspec(dllexport) void  SetConsoleStrIn_Blue_White();
__declspec(dllexport) void  SetConsoleStrIn_Red_Yello();
__declspec(dllexport) void  SetConsoleDefault();

