#include <windows.h>

#ifndef _VISIMAGEUTIL25STRUCT_H_
#define _VISIMAGEUTIL25STRUCT_H_

typedef struct ImageTag
{	
	unsigned char **image;		// �̹�������
	int xsize;					// xsize
	int ysize;					// ysize

	RGBQUAD pPal[256];			// �ȷ�Ʈ ����
	int     palSize;			// �ȷ�Ʈ ����

	BYTE    *pD2RAnno;			// D2RAnnotation ����
	int     D2RAnnoSize;		// D2RAnnotation ������
	
	BYTE	*pAlpha;			// ����ä��(PNG,GIF��)
	
	int		PageNumber;			// ������ ��ȣ
	int		bpp;				// bpp
	int		xRes;				// xResolution
	int		yRes;				// yResolution
	int		format;				// format
	int		compression;		// ��������
	int		photometric;		// �����??(RGB, YBCR, ��Ÿ���)

	char    saveVersion[256];	// �̹��� ��ƿ ���̺� ����

} ImageTag;

typedef struct ImageTag10
{	//RGBQUAD *pal;
	unsigned char **image;
	BYTE *D2RAnno;
	int D2RAnnoSize;
	int PageNumber;
	int xsize;
	int ysize;
	int bpp;
	int xRes;
	int yRes;
	int format;
} ImageTag10;

typedef struct ImageInfo
{	
	int xsize;
	int ysize;
	int bpp;
	int xRes;
	int yRes;
	int format;
	int compression;
	int	photometric;		// �����??(RGB, YBCR, ��Ÿ���)
} ImageInfo;

typedef struct RGBRate
{	
	float r;
	float g;
	float b;
} RGBRate;


typedef struct VIS_RGB
{	
	BYTE r;
	BYTE g;
	BYTE b;

} VIS_RGB;

typedef ImageTag *HIMG;

typedef ImageTag10 *HIMG10;

#define VIS_IMG_FORMAT_TIFF	 1
#define VIS_IMG_FORMAT_JPEG  2 
#define VIS_IMG_FORMAT_J2K   3
#define VIS_IMG_FORMAT_BMP   4
#define VIS_IMG_FORMAT_PNG   5
#define VIS_IMG_FORMAT_GIF   6
#define VIS_IMG_FORMAT_CPR   9 
#define VIS_IMG_FORMAT_PDF   10
#define VIS_IMG_FORMAT_DJVU  11	// Djvu ����
#define VIS_IMG_FORMAT_JBIG  12	// JBIG ����
#define VIS_IMG_FORMAT_XPS   13	// XPS ����
#define VIS_IMG_FORMAT_JBIG2 14	// JBIG2 ����


#define VIS_IMG_FORMAT_IMAGEGEAR  99

#define VIS_BITPERPIXEL_1	1
#define VIS_BITPERPIXEL_8	8
#define VIS_BITPERPIXEL_24	24

#define	    COMPRESSION_CCITTRLE	2		// CCITT modified Huffman RLE
#define	    COMPRESSION_CCITTFAX3	3		// CCITT Group 3 fax encoding
#define	    COMPRESSION_CCITTFAX4	4		// CCITT Group 4 fax encoding
#define	    COMPRESSION_LZW			5       // Lempel-Ziv  & Welch
#define	    COMPRESSION_OJPEG		6		// !6.0 JPEG
#define	    COMPRESSION_JPEG		7		// %JPEG DCT compression

#define     COMPRESSION_JP2000      34712   // Leadtools JPEG2000
#define     COMPRESSION_VISJ2K      34715   // VisualInfosys TIFF IN JPEG2000
#define	    COMPRESSION_JBIG		34661	/* ISO JBIG */
#define	    COMPRESSION_JBIG2		34662   /* 2015.7.5 ����ȣ */
#define     COMPRESSION_JTIF		34720   // TIFF �����⸦ �� JPEG
#define		COMPRESSION_CTIF		34721	// ��ȣȭ�� �̹����� TIFF�� �� ���� 
#define		COMPRESSION_CRYPTOR		34722	// TIFF�� ������ ��ȣȭ�� �̹��� ���� 
#define	    COMPRESSION_PACKBITS	32773	/* Macintosh RLE */


#endif //_VISIMAGEUTIL25STRUCT_H_