#include <windows.h>
#include "VisImageUtil25Struct.h"

#ifdef  __cplusplus
extern "C" {
#endif

/************************************************************************/
/*						compresstype �Ʒ�����							*/
/*
#define	    COMPRESSION_CCITTRLE	2		// CCITT modified Huffman RLE
#define	    COMPRESSION_CCITTFAX3	3		// CCITT Group 3 fax encoding
#define	    COMPRESSION_CCITTFAX4	4		// CCITT Group 4 fax encoding
#define	    COMPRESSION_LZW			5       // Lempel-Ziv  & Welch
#define	    COMPRESSION_OJPEG		6		// !6.0 JPEG
#define	    COMPRESSION_JPEG		7		// %JPEG DCT compression
#define     COMPRESSION_JP2000      34712   // Leadtools JPEG2000
#define     COMPRESSION_VISJ2K      34715   // VisualInfosys TIFF IN JPEG2000
#define     COMPRESSION_JTIF		34720   // TIFF �����⸦ �� JPEG
#define		COMPRESSION_CTIF		34721	// ��ȣȭ�� �̹����� TIFF�� �� ���� 
#define		COMPRESSION_CRYPTOR		34722	// TIFF�� ������ ��ȣȭ�� �̹��� ���� 
/*
/************************************************************************/

/************************************************************************/
/*  Load / Save / Free ���� �Լ�										*/
/************************************************************************/
/* Reduction : ��Һ���..  0--> ����, 1--> 0.5, 2-->0.25, 3-->0.125 .... */
HIMG APIENTRY VIS_LoadImage(char *fileName, int pageNumber, int Reduction, 
							char *pUserKey = NULL);

HIMG APIENTRY VIS_LoadImageRegion(char *fileName,int pageNumber,RECT *r, 
								  char *pUserKey = NULL);


BYTE * APIENTRY VIS_LoadImageResizeBuffer(char *fileName, int pageNumber, int xsize, int ysize, char *pUserKey = NULL);
void APIENTRY VIS_FreeBuffer(BYTE *pBuffer);

HIMG APIENTRY VIS_LoadImageFromDIB(HGLOBAL *hDIB);

HIMG APIENTRY VIS_LoadImageFromHBitmap(HBITMAP hBitmap);

HIMG APIENTRY VIS_LoadImageFromBase64(char *pbuf);

HIMG APIENTRY VIS_LoadFromLowData(unsigned char *pbuf,int buflen, 
								  int xsize, int ysize, int bpp);
int  APIENTRY VIS_FreeImage(HIMG hImage);

int APIENTRY  VIS_SaveImage(HIMG hImage,char *fileName, int format, 
							int quality, int append, int compresstype);

// ���Լ��� JPEG�̹����� TIFF�� �����⸸ �����. ������ ������..
int APIENTRY  VIS_SaveTiffFromFile(char *orgfileName, char *saveFileName,int append);

// ���Լ��� JPEG2000�� ������ ��쿡 ������ �������� �����Ҷ� �ẻ��.
int APIENTRY  VIS_SaveImageExt(HIMG himg,char *fileName, int format, 
							   int quality, int append, int compresstype);

int APIENTRY  VIS_SaveImage_Region(HIMG hImage,char *fileName, int format, 
								   int bit, int quality, int append, RECT *r);

int APIENTRY  VIS_SaveRowData(HIMG hImage,char *fileName);
int APIENTRY  VIS_SaveImageBase64(char *pbuf, char *savefileName);

// ����Ȯ�ο� raw �̹��� ����
int APIENTRY VIS_SaveIRPhoto(HIMG hImage, const char *savefileName, int *sx, int *sy, int *ex, int *ey);

int APIENTRY  VIS_SaveImageEncrypt(HIMG himage, char *fileName,char *pUserKey,
								   int format, int quality, int append, 
								   int compresstype, int compressQulity);

int APIENTRY  VIS_SaveImageEncryptFile(char *orgfileName, char *savefileName, 
									   char *pUserKey, int append);

/* ���⼭���ʹ� DIB����... */
/* Reduction : ��Һ���..  0--> ����, 1--> 0.5, 2-->0.25, 3-->0.125 .... */
HGLOBAL APIENTRY VIS_LoadDIBFromFile(char *fileName, int pageNumber, 
									 int Reduction, char *pUserKey = NULL);
HGLOBAL APIENTRY VIS_LoadDIBFromHimage(HIMG hImage);


int     APIENTRY VIS_FreeDIB(HGLOBAL hDIB);

/************************************************************************/
/*  �̹��� ���� ���� �Լ�                                               */
/************************************************************************/
int APIENTRY  VIS_ConvertBitmap(HIMG hImage,int bpp, RGBRate *rate, 
								int colorType, int fastOpt, int sealOpt);

int APIENTRY  VIS_ConvertBitmapHSB(HIMG hImage, float fromHue, float toHue, float saturation, float lightness);

HGLOBAL APIENTRY VIS_ConvertSealImageDIB(HIMG himg, int bpp);

//1bit ����.. �ӵ��� �� ������..
int APIENTRY  VIS_ConvertBitmapManual(HIMG hImage, int rate);
int APIENTRY  VIS_ConvertImageSize(HIMG hImage, int xsize,int ysize);

// Win32 API�� ����Ͽ� Resize�Ѵ�.
int APIENTRY  VIS_ConvertImageSizeWin32(HIMG himg, int xsize,int ysize); 

int APIENTRY  VIS_RotateImage(HIMG hImage, float angle, 
							  int resizeOpt, int fastOpt);

int APIENTRY  VIS_RotateImageEx(HIMG hImage, float angle, VIS_RGB *rgb);

int APIENTRY  VIS_TrimImage(HIMG hImage, RECT *r);

int APIENTRY  VIS_AutoTrimRect(HIMG hImage, RECT *r);


int APIENTRY  VIS_MosaicBitmap(HIMG hImage, RECT *r, int pixCount,
							   int algorithmtype);
int APIENTRY  VIS_FillRect(HIMG hImage, RECT *r, VIS_RGB *rgb);
int APIENTRY  VIS_CorrectImage(HIMG hImage);
int APIENTRY  VIS_Contrast(HIMG hImage, float rate);


int APIENTRY  VIS_InvertBitmap(HIMG hImage);
int APIENTRY  VIS_SharpenBitmap(HIMG hImage);
int APIENTRY  VIS_GaussianBlur(HIMG hImage, float radius);
int APIENTRY  VIS_UnsharpMask(HIMG hImage, float radius /*= 5.0*/, float amount /*= 0.5*/, int threshold /*= 0*/);

int APIENTRY  VIS_ConvertSealImage(char *pOrgImage, char *pDstImage);

/************************************************************************/
/*  �̹����� ���ھ���													*/
/************************************************************************/
int APIENTRY  VIS_AddString(HIMG hImage,
							int bold, int align, int fontsize, 
							const char *fontName, RECT *rect, 
							VIS_RGB *txtColor,char *text,float angle,
							int Blending, float srcrate, float dstrate);


/************************************************************************/
/*  �̹��� ���� �Լ�													*/
/************************************************************************/
HIMG APIENTRY VIS_CopyBitmap(HIMG hDstimg);
HIMG APIENTRY VIS_CopyBitmapRegion(HIMG hDstimg, RECT *r);

// �̹��� ��ƿ 10������ �̹����� ī���ϵ��� ����
// ��ǥ�� 0,0,0,0 �̸� ��ü���� ī��
HIMG APIENTRY VIS_CopyOldBitmap10(HIMG10 hDstimg, RECT *r);
HIMG APIENTRY VIS_CopyBitmapRawData(unsigned char **image, int xsize, int ysize, int bpp, int xres, int yres);

/************************************************************************/
/*  �̹��� �������� �Լ�                                                */
/************************************************************************/
unsigned char ** APIENTRY  VIS_GetRowData(HIMG hImage);
int APIENTRY  VIS_GetPixelData(HIMG hImage, int x, int y, BYTE *r, BYTE *g, BYTE *b);
int APIENTRY  VIS_GetPixelCount(HIMG hImage, RECT *r,int opt);
int APIENTRY  VIS_FilePageCount(char * fileName);
int APIENTRY  VIS_FilePageInfo(char * fileName, int pageNumber, 
							   ImageInfo *info, char *pUserKey = NULL);
int APIENTRY  VIS_MemoryPageInfo(HIMG hImage, ImageInfo *info);
int APIENTRY  VIS_SetResolution(HIMG hImage, int xres, int yres);
int APIENTRY  VIS_GetSaveModuleVersion(char *fileName, int pageNumber, char *ver);

/************************************************************************/
/*  ��ó�� �����Լ�                                                     */
/************************************************************************/
float APIENTRY  VIS_GetDeskewAngle(HIMG hImage);
float APIENTRY  VIS_GetAnchorAngle(HIMG hImage, RECT *pAnchorRect1, RECT *pAnchorRect2);
int   APIENTRY  VIS_RemoveBorder(HIMG hImage, float rate);
int   APIENTRY  VIS_GetBorderRect(HIMG hImage, int optColor, float rate, RECT *r);
int   APIENTRY  VIS_RemoveNoise(HIMG himg, int nxsize, int nysize);
int   APIENTRY  VIS_RemoveLine(HIMG hImage, int sx, int sy, int ex, int ey, 
							   int bang, int maxlineWidth, int minLength);


/************************************************************************/
/*  �̹��� �̾���̱� (RollImage)                                       */
/************************************************************************/
int   APIENTRY  VIS_AppendImage(HIMG hOrgimg, HIMG hDstimg);
int   APIENTRY  VIS_AppendImageEx(HIMG hOrgimg, HIMG hDstimg);
int   APIENTRY  VIS_AppendImageDIB(HGLOBAL *hDIBOrg, HGLOBAL *hDIBDst);

/************************************************************************/
/*  �̹��� �� hDIBOrg �� hDIBDst �� ������ ���Ѵ�.                  */
/************************************************************************/
int   APIENTRY  VIS_CompareDIB(HGLOBAL *hDIBOrg, HGLOBAL *hDIBDst);

/************************************************************************/
/*  �̹����� �����Ѵ�.													*/
/************************************************************************/
HIMG APIENTRY  VIS_CreateHimage(int xsize, int ysize, int bpp, int res);

/************************************************************************/
/*  �̹��� �ռ� hSrcimg �̹����� hDstimg �̹����� �ռ��Ѵ�.             */
/************************************************************************/
int   APIENTRY  VIS_CombineImage(HIMG hSrcimg, HIMG hDstimg, int sx, int sy);

/************************************************************************/
/*  �̹����ռ� ���� ��������											*/
/************************************************************************/
int   APIENTRY  VIS_CombineImageEx(HIMG hImage,HIMG hdst, int sx, int sy, 
						           int Blending, float srcrate, float dstrate);

/************************************************************************/
/*  �����⸸ TIFF�� ���� �̹����� TIFF Header�� �����Ѵ�.				*/
/************************************************************************/
int	APIENTRY  VIS_ExtractImage(char *srcfileName, char *dstfileName, int pageNumber);

/************************************************************************/
/*  TIFF �̹������� Ư���������� �����Ѵ�.								*/
/************************************************************************/
int	APIENTRY  VIS_ExtractTiffImage(char *srcfileName, char *dstfileName, int pageNumber);

/************************************************************************/
/*  TIFF �̹������� ��ü�������� �����Ѵ�.								*/
/************************************************************************/
int	APIENTRY  VIS_ExtractTiffImageAuto(char *srcfileName, char *savepath, char *prepix, char *pUserKey = NULL);

/************************************************************************/
/*  TIFF �̹������� �����͸� ���� �Ѵ�.								*/
/************************************************************************/
int APIENTRY  VIS_ExtractTiffData(char *fileName, int pageNumber, BYTE *buffer, int *len);

/************************************************************************/
/*  TIFF �̹����� �����ϱ����� �޸𸮸� �Ҵ�޴´�.						*/
/************************************************************************/
HANDLE	APIENTRY  VIS_OpenAppender(char *fileName);
/************************************************************************/
/*  TIFF�̸̹� Append�Ѵ�.						*/
/************************************************************************/
int		APIENTRY  VIS_AppendTiffImage(HANDLE hAppender, char *fileName);
/************************************************************************/
/*  VIS_OpenAppender���� �Ҵ���� �޸𸮸� Release�Ѵ�.					*/
/************************************************************************/
void	APIENTRY  VIS_CloseAppender(HANDLE hAppender);

/************************************************************************/
/*  �ε�� �̹������� ������̼� ������ �����Ѵ�.						*/
/************************************************************************/
void APIENTRY  VIS_DeleteAnnotation(HIMG hImage);

/************************************************************************/
/*  �������� �Լ�														*/
/************************************************************************/
int APIENTRY  VIS_GetLastError(char *errDescription);

/************************************************************************/
/*  �������� �Լ�														*/
/************************************************************************/
void APIENTRY  VIS_GetVersion(char *ver);

/************************************************************************/
/*  �������� ���														*/
/************************************************************************/
int  APIENTRY  VIS_GetModulePath(char *path);

void APIENTRY  VIS_DrawImage(HIMG himg,int hwnd);

#ifdef  __cplusplus
}
#endif
