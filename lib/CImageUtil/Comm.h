//
//  Comm.h
//  VisImageUtil25
//
//  Created by oh seokho on 2014. 10. 22..
//  Copyright (c) 2014년 oh seokho. All rights reserved.
//

#ifndef _COMM_H_
#define _COMM_H_

typedef unsigned int   UINT;
typedef unsigned char  BYTE;
typedef unsigned long  DWORD;
typedef unsigned short WORD;
typedef unsigned long  COLORREF;
typedef void *HANDLE;

typedef struct tagRGBQUAD
{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
} RGBQUAD;

typedef struct RECT
{
    long left;
    long top;
    long right;
    long bottom;
    
} RECT;

#endif