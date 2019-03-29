#pragma once

#ifdef MATUREAPPROACH_EXPORTS
#define MATUREAPPROACH_API __declspec(dllexport)
#else
#define MATUREAPPROACH_API __declspec(dllimport)
#endif

class IExport
{
public:
	virtual void Hi() = 0;
	virtual void Test() = 0;
	virtual void Release() = 0;
};


extern "C" MATUREAPPROACH_API IExport* _stdcall CreateExportObj();
extern "C" MATUREAPPROACH_API void _stdcall DestroyExportObj(IExport* pExport);

