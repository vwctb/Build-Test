#include "CImageUtil.h"

/************************************************************************/
/*					Public Function	                                    */
/************************************************************************/

CImageUtil::CImageUtil()
{

}
CImageUtil::CImageUtil(char *moduleName, char *moduleVesion)
{

}

CImageUtil::~CImageUtil()
{
}

ImageTag * CImageUtil::LoadImageBuffer(char *buffer, int bufSize, int pageNumber, int Reduction, RECT *r, char *pUserKey, int bitOrder)
{

	ImageTag *hImage = NULL;
	int format;
	bool bflag = false ;
	int errorCode=0;
	
	format = GetImageType(buffer);
	
	if(pageNumber==0)
		pageNumber=1;

	if (format == VIS_IMG_FORMAT_JPEG)
	{
		hImage = (ImageTag *)malloc(sizeof(ImageTag));

		if (hImage == NULL)
		{
			return 0;
		}

		InitHIMG(hImage);

		hImage->image = Load_JPEG_Buffer((unsigned char*)buffer,bufSize,&hImage->xsize,&hImage->ysize,&hImage->bpp,&hImage->xRes,&hImage->yRes);
		hImage->PageNumber = 1;
		hImage->format = VIS_IMG_FORMAT_JPEG;
		
		if (hImage->image != 0)
		{
			return hImage;
		}else
		{
			return 0;
		}
	}else
	{
		return 0;
	}
}

int CImageUtil::GetImageType(char * buffer)
{

	BYTE buf[32];
	int len = 0;
	int format = 0;

	memcpy(buf,(const char *) buffer, 20);


	if(buf[0] == 0xFF && buf[1] == 0xD8)
	{
		format = VIS_IMG_FORMAT_JPEG;
	}else if(buf[0] =='B' && buf[1] =='M')
	{
		format = VIS_IMG_FORMAT_BMP;
	}else if((buf[0] == 'M' && buf[1] == 'M' && buf[2] == 0 && buf[3] == 42)
		|| (buf[0] == 'I' && buf[1] == 'I' && buf[2] == 42 && buf[3] == 0))
	{
		format = VIS_IMG_FORMAT_TIFF;
	}else if(buf[4] == 'j' && buf[5] == 'P')
	{
		format = VIS_IMG_FORMAT_J2K;
	}else if (buf[1] == 'P' && buf[2] == 'N' && buf[3] == 'G' )
	{
		format = VIS_IMG_FORMAT_PNG;
	}else if (buf[0] == 'G' && buf[1] == 'I' && buf[2] == 'F' )
	{
		format = VIS_IMG_FORMAT_GIF;
	}else if (buf[0] == '%' && buf[1] == 'P' && buf[2] == 'D' &&  buf[3] == 'F')
	{
		format = VIS_IMG_FORMAT_PDF;
	}else if (buf[0] == 'A' && buf[1] == 'T' && buf[2] == '&' &&  buf[3] == 'T')
	{
		format = VIS_IMG_FORMAT_DJVU;
	}else
	{
		format = 0;
	}
	
	return format;
}



void CImageUtil::InitHIMG(ImageTag *hImage)
{
	hImage->bpp = 0;
	hImage->pD2RAnno = NULL;
	hImage->D2RAnnoSize = 0;
	hImage->palSize = 0;
	hImage->format = 0;
	hImage->image = 0;
	hImage->PageNumber = 0;
	hImage->xRes = 0;
	hImage->xsize = 0;
	hImage->yRes = 0;
	hImage->ysize = 0;
	hImage->compression = 0;
	hImage->pAlpha = NULL;
	hImage->saveVersion[0] = 0x00;
	hImage->photometric = 0;

}

int CImageUtil::FreeHImage(ImageTag *himg)
{

	if (himg)
	{
		try
		{
			ImageTag *img = (ImageTag *) himg;

			if (img->xsize>0 && img->ysize>0 && 
				img->PageNumber >0 && img->bpp>0)
			{
				FreeImage(img->image,img->ysize);

				if (img->D2RAnnoSize > 0) 
					free(img->pD2RAnno);

				if (img->pAlpha > 0) 
					free(img->pAlpha);

				free(img);
				img=0;

				return 1;
			}else
			{	
				//SetLastError(-98);
				return 0;
			}
		}
		catch (...)
		{
			//SetLastError(-98);
			return 0;
		}

	}else
	{
		//SetLastError(-99);
		return 0;
	}
}

void CImageUtil::FreeImage(unsigned char **image, int ysize)
{
	int y;

	if (ysize>0)
	{
		for (y=0;y<ysize;y++)
			free(image[y]);

		free(image);
		image = 0;
	}

}
