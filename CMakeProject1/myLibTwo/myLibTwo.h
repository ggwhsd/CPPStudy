// myLibTwo.h: 目标的头文件。

#pragma once


#ifdef _WINDOWS    //windows  
#ifdef DLL_EXPORTS    // windows create dll project
#define DLL_API extern "C" __declspec(dllexport)
#else    //windows use dll project
#define DLL_API extern "C" __declspec(dllimport)
#endif
#else    //linux
#define DLL_API
#endif

DLL_API int DynamicLibMethod(int a, int b);