#include "CImageUtil.h"
#include "./lib/INFOLIBJPEG.h"

/************************************************************************/
/*					Public Function	                                    */
/************************************************************************/

CImageUtil::CImageUtil()
{
	m_Version[0] = 0x00;
}
CImageUtil::CImageUtil(char *moduleName, char *moduleVesion)
{
	strcpy(m_Name,(const char*)moduleName);
	strcpy(m_Version,(const char*)moduleVesion);
}

CImageUtil::~CImageUtil()
{
}

HIMG CImageUtil::LoadImage(char *fileName, int pageNumber, int Reduction, RECT *r, char *pUserKey, int bitOrder)
{

	ImageTag *hImage = NULL;
	char pOrgfileName[256];
	int	bufSize=0;
	int format;
	int ret;
	bool bflag = false ;
	int errorCode=0;

	strcpy(pOrgfileName,(const char *)fileName);
		
	format = GetImageType(fileName);
	
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

		hImage->image = Load_JPEG((unsigned char*)pOrgfileName,&hImage->xsize,&hImage->ysize,&hImage->bpp,&hImage->xRes,&hImage->yRes,&errorCode);
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


int CImageUtil::SaveImage(HIMG himg,char *fileName, int format, int quality, int append, int compresstype, int compressQulity)
{
	char version[256];
	int ret=0;	

	if (himg)
    {
		if (format == VIS_IMG_FORMAT_JPEG)
		{
			ret = Save_JPEG((unsigned char *)fileName,himg->image,himg->xsize,himg->ysize,himg->bpp,himg->yRes,quality);
			return ret;
		}
			
		return 0;

	}else
	{	
		return 0;
	}

}



int CImageUtil::GetImageType(char * fileName)
{

	BYTE buf[32];
	FILE *fr;
	int len = 0;
	int format = 0;

	fr = fopen(fileName,"rb");

	if(fr == NULL) 
		return 0;

	len= fread(buf,1,20,fr);

	fclose(fr);

 	if(len)
 	{	
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
	}

	
	return format;
}



void CImageUtil::InitHIMG(ImageTag *img)
{
	img->bpp = 0;
	img->pD2RAnno = NULL;
	img->D2RAnnoSize = 0;
	img->palSize = 0;
	img->format = 0;
	img->image = 0;
	img->PageNumber = 0;
	img->xRes = 0;
	img->xsize = 0;
	img->yRes = 0;
	img->ysize = 0;
	img->compression = 0;
	img->pAlpha = NULL;
	img->saveVersion[0] = 0x00;
	img->photometric = 0;

}



int CImageUtil::FreeHImage(HIMG himg)
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
				SetLastError(-98);
				return 0;
			}
		}
		catch (...)
		{
			SetLastError(-98);
			return 0;
		}

	}else
	{
		SetLastError(-99);
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
