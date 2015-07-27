#include "CImageUtilHtml5.h"
#include "CImageUtil.h"
#include "CBase64.h"

CImageUtilHtml5::CImageUtilHtml5()
{

}

CImageUtilHtml5::~CImageUtilHtml5()
{
}

char * CImageUtilHtml5::LoadImageBuffer(char *inbufferBase64, int bufSize, int pageNumber)
{	
	CImageUtil ImageUtil;
	CBase64  Base64;
	char *inbuffer;
	int  insize;
	char *outBuffer;
	int  size;
	int  count=0;
	int  y,x;

	insize = Base64.Base64_DecodeLen(inbufferBase64);

	inbuffer = (char *)malloc(insize);
	Base64.Base64_Decode(inbuffer,(const char *)inbufferBase64);

	ImageTag * hImage = ImageUtil.LoadImageBuffer(inbuffer,insize,1,0,NULL,NULL,0);

	free(inbuffer);

	if (hImage)
	{
		size = hImage->xsize * hImage->ysize * 4;
		outBuffer = (char *)malloc(size);
		memset(outBuffer,0x00,size);

		for (y=0;y<hImage->ysize;y++)
		{
			for (x=0;x<hImage->xsize;x++)
			{
				outBuffer[count+0] = hImage->image[y][x*3+0];
				outBuffer[count+1] = hImage->image[y][x*3+1];
				outBuffer[count+2] = hImage->image[y][x*3+2];

				count += 4;
			}

			if (count > size)
				break;
		}

		// base64 encoding
		char *outBufferBase64;
		int  outsize = size * 2;
		
		outBufferBase64 = (char *)malloc(outsize);
		memset(outBufferBase64,0x00,outsize);

		Base64.Base64_Encode(outBufferBase64,(const char *)outBuffer,size);

		/*
		imageInfo->xsize			= hImage->xsize;
		imageInfo->ysize			= hImage->ysize;
		imageInfo->bufferSize	= strlen(outBufferBase64);
		*/

		ImageUtil.FreeHImage(hImage);
		free(outBuffer);

		return outBufferBase64;
	}else
	{
		return 0;
	}

}