/* 
	INFOLIBJPEG.h

    Copyright by VisualInfosys Co., Ltd 2003-2009
    All rights reserved.
 
    defined for 32-bit environment
    may need porting if working for 64-bit environment
	
	작성자 : 오석호
	최초 작성일 : 2009.1.19
	Current Version : 1.0.0.2
*/


#ifndef _INFOLIBJPEG_H_
#define _INFOLIBJPEG_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define SJPEG_QUALITYBAD		10
#define SJPEG_QUALITYAVERAGE	25
#define SJPEG_QUALITYNORMAL		50
#define SJPEG_QUALITYGOOD		75
#define SJPEG_QUALITYSUPERB		100

unsigned char **Load_JPEG_Buffer(unsigned char *buffer, int bufsize,int *xsize, int *ysize, int *bpp, int *xdpi, int *ydpi);
unsigned char * Save_JPEG_Buffer(unsigned char **image, int xsize, int ysize, int bpp, int dpi, int quality, int *outsize);

#ifdef  __cplusplus
}
#endif

#endif