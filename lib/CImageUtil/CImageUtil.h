
#include "VisImageUtil25Struct.h"
#include "INFOLIBJPEG/INFOLIBJPEG.h"
#include "Comm.h"

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

	ImageTag *LoadImageBuffer(char *buffer, int bufSize, int pageNumber, int Reduction, RECT *r, char *pUserKey, int bitOrder);
	char * SaveImageBuffer(char *inbuffer, int bufSize, int xsize, int ysize, int bpp);

	int  FreeHImage(ImageTag *hImage);

/************************************************************************/
/*              Protected Function										*/
/************************************************************************/
private:
	int  GetImageType(char * buffer);
	void InitHIMG(ImageTag *img);
	void FreeImage(unsigned char **image, int ysize);


/************************************************************************/
/*              Protected Member										*/
/************************************************************************/
private:
	
	int  m_ErrCode;
};
