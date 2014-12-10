
#include "tgautils.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct {
	char		idlength;
	char		colourmaptype;
	char		datatypecode;
	short int	colourmaporigin;
	short int	colourmaplength;
	char		colourmapdepth;
	short int	x_origin;
	short int	y_origin;
	unsigned short	width;
	unsigned short	height;
	char		bytesperpixel;
	char		imagedescriptor;
} HEADER;

char* import_tga(char* filename, int& width, int& height) {
	FILE *fptr;
	HEADER header;
	char* pixels;
	int total;

	if ((fptr = fopen(filename,"r")) == NULL) {
		fprintf(stderr, "File open failed\n");
		exit(-1);
	}

	/* Read the header fields */
	header.idlength = fgetc(fptr);
	header.colourmaptype = fgetc(fptr);
	header.datatypecode = fgetc(fptr);
	fread(&header.colourmaporigin, 2, 1, fptr);
	fread(&header.colourmaplength, 2, 1, fptr);
	header.colourmapdepth = fgetc(fptr);
	fread(&header.x_origin, 2, 1, fptr);
	fread(&header.y_origin, 2, 1, fptr);
	fread(&header.width, 2, 1, fptr);
	fread(&header.height, 2, 1, fptr);
	header.bytesperpixel = fgetc(fptr);
	header.imagedescriptor = fgetc(fptr);

	header.bytesperpixel = header.bytesperpixel / 8;
	if((header.bytesperpixel != 3) && (header.bytesperpixel != 4)) {
		fprintf(stderr, "File not valid\n");
		exit(-1);
	}

	#ifdef __BIG_ENDIAN__
	header.width = (header.width >> 8) | (header.width << 8);
	header.height = (header.height >> 8) | (header.height << 8);
	#endif

	total = header.width * header.height * header.bytesperpixel;

	/* Allocate space for the image */
	if ((pixels = (char*)malloc(total * sizeof(char))) == NULL) {
		fprintf(stderr, "malloc of image failed\n");
		exit(-1);
	}

	/* Read the image, data are stored in the BGR[A] form */ 
	for(int i = 0; i < total; i += header.bytesperpixel) {
		pixels[i+2] = fgetc(fptr);
		pixels[i+1] = fgetc(fptr);
		pixels[i] = fgetc(fptr);
		if(header.bytesperpixel == 4)
			pixels[i+3] = fgetc(fptr);
	}

	fclose(fptr);

	width = header.width;
	height = header.height;
	return pixels;
}

GLuint load_tex(char* name, bool mipmap) {
	GLuint texture;
	int sizeX;
	int sizeY;
	char* data;

	data = import_tga(name, sizeX, sizeY);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if(mipmap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, sizeX, sizeY, GL_RGB, GL_UNSIGNED_BYTE, data );
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	free(data);
	return texture;
}
