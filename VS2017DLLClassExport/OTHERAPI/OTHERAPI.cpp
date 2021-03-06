// OTHERAPI.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "./b.h"
#include "./ExportClassImpl.h"

MATUREAPPROACH_API IExport* APIENTRY CreateExportObj()
{
	return new ExportImpl;
}


//这里不能直接delete pExport，因为没有把IExport的析构函数定义为虚函数
MATUREAPPROACH_API void  APIENTRY DestroyExportObj(IExport* pExport)
{
	pExport->Release();
}