#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include "CImageUtil.h"
#include "VisImageUtil25.h"

int  m_errCode;
char m_errDesc[1024];
char m_ModuleVersion[256];
char m_ModuleName[256];

extern "C" int APIENTRY

DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return 1;
}

/************************************************************************/
/*  Load / Save / Free 관련 함수										*/
/************************************************************************/
HIMG APIENTRY VIS_LoadImage(char *fileName, int pageNumber, int Reduction, char *pUserKey)
{
	CImageUtil CimgUtil;
	
	HIMG hImage = CimgUtil.LoadImage(fileName,pageNumber,Reduction,NULL,pUserKey,0);

	if (hImage == NULL)
	{
		return 0;
	}
	
	return hImage;

}

int APIENTRY  VIS_SaveImage(HIMG himg,char *fileName, int format, int quality, int append, int compresstype)
{
	int ret;

	CImageUtil CimgUtil(m_ModuleName,m_ModuleVersion);
	ret = CimgUtil.SaveImage(himg,fileName,format,quality,append,compresstype);

	if (ret != 1)
	{
		return 0;
	}

	return ret;
}

int APIENTRY  VIS_FreeImage(HIMG hImage)
{
	int ret;

	CImageUtil CimgUtil(m_ModuleName,m_ModuleVersion);
	ret = CimgUtil.FreeHImage(hImage);

	if (ret != 1)
	{
		return 0;
	}

	return ret;
}
