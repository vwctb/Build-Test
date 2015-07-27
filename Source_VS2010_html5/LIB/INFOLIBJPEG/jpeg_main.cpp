#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>


#include "INFOLIBJPEG.h"

// ==========================================================
//   JPEG LOAD/SAVE MODULE
// ==========================================================

#define INPUT_BUF_SIZE  4096	/* choose an efficiently fread'able size */
#define OUTPUT_BUF_SIZE 4096    /* choose an efficiently fwrite'able size */
typedef struct my_error_mgr * my_error_ptr;

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

METHODDEF(void)
jpeg_error_exit (j_common_ptr cinfo) {
	(*cinfo->err->output_message)(cinfo);

	jpeg_destroy(cinfo);
}

METHODDEF(void)
jpeg_output_message (j_common_ptr cinfo) {
	char buffer[JMSG_LENGTH_MAX];

	(*cinfo->err->format_message)(cinfo, buffer);
}

#include "jinclude.h"
#include "jerror.h"


// Expanded data source object for stdio input --------------

struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */

	jmp_buf setjmp_buffer;	/* for return to caller */
};
// ----------------------------------------------------------


unsigned char **Load_JPEG( unsigned char *fname,int *xsize, int *ysize, int *bpp, int *xdpi, int *ydpi, int *errorCode)
{
	int i,y,x;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE * infile;		/* source file */
	unsigned char **image;
	int ret;

	*errorCode = 0;
	
	if ((infile = fopen((const char *)fname, "rb")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", fname);
		*errorCode = -998;
		return 0;
	}
	cinfo.err = jpeg_std_error(&jerr);

	jerr.error_exit     = jpeg_error_exit;
	jerr.output_message = jpeg_output_message;

	
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* specify data source (eg, a file) */
	jpeg_stdio_src(&cinfo, infile);

	jpeg_read_header(&cinfo, TRUE);

	// set parameters for decompression
	cinfo.dct_method          = JDCT_IFAST;
	cinfo.do_fancy_upsampling = FALSE;
		

	*xsize = cinfo.image_width;
	*ysize = cinfo.image_height;
	*bpp = 8 * cinfo.num_components;
	*xdpi = cinfo.X_density;
	*ydpi = cinfo.Y_density;
	
	if (*xsize == 0 || *ysize ==0)
	{
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return 0;
	}

	if (!jpeg_start_decompress(&cinfo))
	{
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return 0;
	}
	
	// start decompressor
	//jpeg_start_decompress(&cinfo);

	image = (unsigned char **)malloc(sizeof(unsigned char *)*cinfo.image_height);

	if (image ==NULL)
	{
		*errorCode = -999;
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return 0;
	}

	for(i=0; i<(int)cinfo.image_height; i++)
	{
		image[i] = (unsigned char*)malloc(cinfo.image_width*cinfo.num_components);
		
		if (image[i] ==NULL)
		{
			fclose(infile);
			jpeg_destroy_decompress(&cinfo);
			*errorCode = -999;
			return 0;
		}
	}
	

	//while (scan lines remain to be read) jpeg_read_scanlines(...);
	while (cinfo.output_scanline < cinfo.output_height) 
	{
		ret =  jpeg_read_scanlines(&cinfo, &image[cinfo.output_scanline], 1);

		if (ret != 1)
		{
			ret = 0;
		}
	}
	// finish decompression
	jpeg_finish_decompress(&cinfo);

	// release JPEG decompression object
	jpeg_destroy_decompress(&cinfo);
	
	fclose(infile);

	if (*bpp==8)
	{
		unsigned char **gimage;
		
		gimage = (unsigned char **)malloc(sizeof(unsigned char *) * *ysize);
		
		if (gimage ==NULL)
		{
			*errorCode = -999;
			jpeg_destroy_decompress(&cinfo);
			fclose(infile);
			return 0;
		}

		for(i=0; i<*ysize;i++)
		{
			gimage[i] = (unsigned char *)malloc(*xsize*3);

			if (gimage[i] ==NULL)
			{
				*errorCode = -999;
				jpeg_destroy_decompress(&cinfo);
				fclose(infile);
				return 0;
			}

		}
		
		for (y=0;y<*ysize;y++)
		{
			for (x=0;x<*xsize;x++)
			{
				gimage[y][x*3+0] = image[y][x];
				gimage[y][x*3+1] = image[y][x];
				gimage[y][x*3+2] = image[y][x];
			}
		}
		
		for (y=0;y<*ysize;y++)
		{
			free(image[y]);
		}
		
		free(image);
		
		return gimage;

	}else
	{
		return image;
	}

}




// ----------------------------------------------------------
unsigned char **Load_JPEG_Region( unsigned char *fname,int x1,int y1, int x2, int y2,int *xsize, int *ysize, int *bpp,int *xdpi, int *ydpi)
{
	int i;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE * infile;		/* source file */
	unsigned char **image;
	unsigned char **ResImg;
	unsigned char **gimage;
	int xs,ys,oxsize,oysize,x,y;
	int left,top,right,bottom;

	if ((infile = fopen(fname, "rb")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", fname);
		return 0;
	}
	cinfo.err = jpeg_std_error(&jerr);

	jerr.error_exit     = jpeg_error_exit;
	jerr.output_message = jpeg_output_message;

	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* specify data source (eg, a file) */
	jpeg_stdio_src(&cinfo, infile);

	jpeg_read_header(&cinfo, TRUE);

	// set parameters for decompression
	cinfo.dct_method          = JDCT_IFAST;
	cinfo.do_fancy_upsampling = FALSE;

	oxsize = cinfo.image_width;
	oysize = cinfo.image_height;
	*bpp = 8 * cinfo.num_components;
	*xdpi = cinfo.X_density;
	*ydpi = cinfo.Y_density;

	// start decompressor
	jpeg_start_decompress(&cinfo);

	image = (unsigned char **)malloc(sizeof(unsigned char *)*cinfo.image_height);
	for(i=0; i< (int)cinfo.image_height; i++)
		image[i] = malloc(cinfo.image_width*cinfo.num_components);

	//while (scan lines remain to be read) jpeg_read_scanlines(...);
	while (cinfo.output_scanline < cinfo.output_height) 
	{
		jpeg_read_scanlines(&cinfo, &image[cinfo.output_scanline], 1);
	}
	// finish decompression
	jpeg_finish_decompress(&cinfo);

	// release JPEG decompression object
	jpeg_destroy_decompress(&cinfo);

	fclose(infile);

	left = x1; if(left < 0) left = 0;
	right = x2; if(right >= oxsize) right = oxsize-1;
	top = y1; if(top < 0) top = 0;
	bottom = y2; if(bottom >= oysize) bottom = oysize-1;

	xs = right-left+1;
	ys = bottom-top+1;
	if(xs < 0 || ys < 0)
	{
		for(i=0; i<oysize; i++)
			free(image[i]);
		free(image);
		return 0;
	}

	if(*bpp == 8)
	{
		*xsize = xs;
		*ysize = ys;
		
		gimage = (unsigned char **)malloc(sizeof(unsigned char *) * ys);
		
		for(i=0; i<ys;i++)
		{
			gimage[i] = (unsigned char *)malloc(sizeof(unsigned char) * xs * 3);
		}
		
		for (y=top;y<bottom;y++)
		{
			for (x=left;x<right;x++)
			{
				gimage[y-top][(x-left)*3+0] = image[y][x];
				gimage[y-top][(x-left)*3+1] = image[y][x];
				gimage[y-top][(x-left)*3+2] = image[y][x];
			}
		}
		
		for (y=0;y<oysize;y++)
		{
			free(image[y]);
		}
	
		free(image);

		return gimage;

	}else if(*bpp == 24)
	{
		ResImg = malloc(sizeof(unsigned char *)*ys);
		for(i=0; i<ys; i++)
		{
			ResImg[i] = malloc(xs*3);
			memcpy(ResImg[i],&image[i+top][left*3],xs*3);
		}
		for(i=0; i<oysize; i++)
			free(image[i]);
		free(image);
		*xsize = xs;
		*ysize = ys;
		return (ResImg);
	}
	else
	{
		for(i=0; i<oysize; i++)
			free(image[i]);
		free(image);
		return 0;
	}
}

#define S_MINISBLACK  1		// min value is black
#define S_RGB         2		// RGB color model

#define SJPEG_QUALITYBAD		10
#define SJPEG_QUALITYAVERAGE	25
#define SJPEG_QUALITYNORMAL		50
#define SJPEG_QUALITYGOOD		75
#define SJPEG_QUALITYSUPERB		100

int Save_JPEG(unsigned char *fname, 
			  unsigned char **image,
			  int xsize, int ysize,
			  int bpp,
			  int dpi,
			  int quality)
{
	int color_type;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE * outfile;		/* target file */


	if ((outfile = fopen((const char *)fname, "wb")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", fname);
		return 0;
	}

	if ((bpp != 24) && (bpp != 8))
		return 0;
	else 
	{
		if(bpp == 24)			color_type = S_RGB;
		else					color_type = S_MINISBLACK;
	}
	// Step 1: allocate and initialize JPEG compression object
	cinfo.err = jpeg_std_error(&jerr);

	jerr.error_exit     = jpeg_error_exit;
	jerr.output_message = jpeg_output_message;

	/* Now we can initialize the JPEG compression object. */

	jpeg_create_compress(&cinfo);

	/* specify data destination (eg, a file) */

	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = xsize;
	cinfo.image_height = ysize;

	if(color_type == S_MINISBLACK)
	{
		/* 
		오석호 수정 아래코드는 테스트로 해본거 같은디 쩝.. 옵션을 저걸로 주면 아웃
		cinfo.in_color_space = JCS_RGB;
		*/
		
		cinfo.in_color_space = JCS_GRAYSCALE;
		cinfo.input_components = 1;
	}
	else
	{
		cinfo.in_color_space = JCS_RGB;
		cinfo.input_components = 3;
	}
	jpeg_set_defaults(&cinfo);

	cinfo.density_unit = 1; // dots/inch
	cinfo.X_density = dpi;
	cinfo.Y_density = dpi;

	jpeg_set_quality(&cinfo, quality, TRUE); /* limit to baseline-JPEG values */

	/*  Start compressor */
	jpeg_start_compress(&cinfo, TRUE);

	/* Step 6: while (scan lines remain to be written) */

	if (bpp == 8)
	{
		unsigned char **gimage;
		int x,y;

		gimage = (unsigned char **)malloc(sizeof(unsigned char *) * ysize);
		
		for(y=0; y<ysize;y++)
		{
			gimage[y] = (unsigned char *)malloc(sizeof(unsigned char) * xsize);

			for (x=0;x<xsize;x++)
			{
				gimage[y][x] = (unsigned char)((image[y][x*3+0] * 0.299) +
					                           (image[y][x*3+1] * 0.587) + 
											   (image[y][x*3+2] * 0.114));
			}
		}

		while (cinfo.next_scanline < cinfo.image_height) 
		{
			// write the scanline
			jpeg_write_scanlines(&cinfo, &gimage[cinfo.next_scanline], 1);
		}

		for(y=0; y<ysize;y++)
		{
			free(gimage[y]);
		}

		free(gimage);

	}else
	{
		while (cinfo.next_scanline < cinfo.image_height) 
		{
			// write the scanline
			jpeg_write_scanlines(&cinfo, &image[cinfo.next_scanline], 1);
		}

	}

	jpeg_finish_compress(&cinfo);

	jpeg_destroy_compress(&cinfo);

	fclose(outfile);

	return 1;
}


int GetJpegInfo( unsigned char *fname, int *xsize,int *ysize, int *bpp, int *xRes, int *yRes)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE * infile;		/* source file */

	if ((infile = fopen(fname, "rb")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", fname);
		return 0;
	}
	cinfo.err = jpeg_std_error(&jerr);

	jerr.error_exit     = jpeg_error_exit;
	jerr.output_message = jpeg_output_message;

	
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* specify data source (eg, a file) */
	jpeg_stdio_src(&cinfo, infile);

	jpeg_read_header(&cinfo, TRUE);

	// set parameters for decompression
	cinfo.dct_method          = JDCT_IFAST;
	cinfo.do_fancy_upsampling = FALSE;

	*xsize = cinfo.image_width;
	*ysize = cinfo.image_height;
	*bpp = 8 * cinfo.num_components;
	*xRes = cinfo.X_density;
	*yRes = cinfo.Y_density;

	// release JPEG decompression object
	jpeg_destroy_decompress(&cinfo);

	fclose(infile);
	return 1;
}