#include <windows.h>
#include <stdio.h>
#include <io.h>
#include "VisImageUtil25Struct.h"

typedef struct FPoint
{	
	float x;
	float y;
	
	FPoint(float _x,float _y){x = _x;y = _y;};
	FPoint(){x = 0;y = 0;};
	
} FPoint;


typedef struct PalletIDX
{
	int idx;
}PalletIDX;

class CImageUtil
{
/************************************************************************/
/*              Public Function											*/
/************************************************************************/
public:
	
	CImageUtil();
	CImageUtil(char *moduleName, char *moduleVesion);
	~CImageUtil();

	HIMG LoadImage(char *fileName, int pageNumber, int Reduction, RECT *r, char *pUserKey, int bitOrder);
	int  SaveImage(HIMG himg,char *fileName, int format, int quality, int append, int compresstype, int compressQulity = 1);

	int  FreeHImage(HIMG himg);

/************************************************************************/
/*              Protected Function										*/
/************************************************************************/
private:
	int  GetImageType(char * fileName);
	void InitHIMG(ImageTag *img);
	void FreeImage(unsigned char **image, int ysize);


/************************************************************************/
/*              Protected Member										*/
/************************************************************************/
private:
	
	char m_Name[256];
	char m_Version[256];
	char m_ErrDesc[1024];
	int  m_ErrCode;
};
