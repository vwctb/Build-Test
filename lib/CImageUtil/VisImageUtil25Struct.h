#ifndef _VISIMAGEUTIL25STRUCT_H_
#define _VISIMAGEUTIL25STRUCT_H_

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Comm.h"

typedef struct ImageTag
{	
	unsigned char **image;		// 이미지정보
	int xsize;					// xsize
	int ysize;					// ysize
	RGBQUAD pPal[256];			// 팔렛트 정보
	int     palSize;			// 팔렛트 갯수
	BYTE    *pD2RAnno;			// D2RAnnotation 정보
	int     D2RAnnoSize;		// D2RAnnotation 사이즈
	BYTE	*pAlpha;			// 알파채널(PNG,GIF등)
	int		PageNumber;			// 페이지 번호
	int		bpp;				// bpp
	int		xRes;				// xResolution
	int		yRes;				// yResolution
	int		format;				// format
	int		compression;		// 압축형식
	int		photometric;		// 영상모델??(RGB, YBCR, 기타등등)
	char    saveVersion[256];	// 이미지 유틸 세이브 버전
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
	int	photometric;		// 영상모델??(RGB, YBCR, 기타등등)
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

//typedef ImageTag10 *HIMG10;

#define VIS_IMG_FORMAT_TIFF	 1
#define VIS_IMG_FORMAT_JPEG  2 
#define VIS_IMG_FORMAT_J2K   3
#define VIS_IMG_FORMAT_BMP   4
#define VIS_IMG_FORMAT_PNG   5
#define VIS_IMG_FORMAT_GIF   6
#define VIS_IMG_FORMAT_CPR   9 
#define VIS_IMG_FORMAT_PDF   10
#define VIS_IMG_FORMAT_DJVU  11	// Djvu 포멧
#define VIS_IMG_FORMAT_JBIG  12	// JBIG 포멧
#define VIS_IMG_FORMAT_XPS   13	// XPS 포멧
#define VIS_IMG_FORMAT_JBIG2 14	// JBIG2 포멧


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
#define	    COMPRESSION_JBIG2		34662   /* 2015.7.5 오석호 */
#define     COMPRESSION_JTIF		34720   // TIFF 껍데기를 싼 JPEG
#define		COMPRESSION_CTIF		34721	// 암호화된 이미지를 TIFF로 싼 포멧 
#define		COMPRESSION_CRYPTOR		34722	// TIFF를 제외한 암호화된 이미지 포멧 
#define	    COMPRESSION_PACKBITS	32773	/* Macintosh RLE */


#endif //_VISIMAGEUTIL25STRUCT_H_