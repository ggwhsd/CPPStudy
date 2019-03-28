#pragma comment(lib,"Dll1.lib")
//__declspec(dllimport) void show(void);
//__declspec(dllimport) int panny(int i, int(*call_back)(int a, int b));
__declspec(dllimport) void showStrIn_Blue(char *);
__declspec(dllimport) void showStrIn_Red_Yello(char *);
__declspec(dllimport) void  SetConsoleStrIn_Blue_White();
__declspec(dllimport) void  SetConsoleStrIn_Red_Yello();
__declspec(dllimport) void  SetConsoleDefault();