#include <stdlib.h>
#include <stdio.h>

typedef struct ImageUtilHtml5_ImageInfo
{	
	int bufferSize;				// 버퍼사이즈
	int xsize;					// xsize
	int ysize;					// ysize

} ImageUtilHtml5_ImageInfo;

class CImageUtilHtml5
{
	/************************************************************************/
	/*              Public Function											*/
	/************************************************************************/
public:

	CImageUtilHtml5();
	~CImageUtilHtml5();

	char * LoadImageBuffer(char *inbufferBase64, int size, int pageNumber);

	/************************************************************************/
	/*              Protected Function										*/
	/************************************************************************/
private:
	
	/************************************************************************/
	/*              Protected Member										*/
	/************************************************************************/
private:

};
