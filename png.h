// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef PNG_H
#define PNG_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "graphicobject.h"
#include "bitmap.h"

typedef struct png
{
  int width;
  int height;
  unsigned char* pixels;
} PNG;

#define FASTPNGLIB_STDCALL 
#define FASTPNGLIB_CALLBACK FASTPNGLIB_STDCALL

typedef FILE* (FASTPNGLIB_CALLBACK *FASTPNGLIB_FILE_OPENCALLBACK) (const char* filename, const char* mode);
typedef int (FASTPNGLIB_CALLBACK *FASTPNGLIB_FILE_CLOSECALLBACK) (FILE* stream);
typedef long (FASTPNGLIB_CALLBACK *FASTPNGLIB_FILE_TELLCALLBACK) (FILE* stream);
typedef int (FASTPNGLIB_CALLBACK *FASTPNGLIB_FILE_SEEKCALLBACK) (FILE* stream, long offset, int whence);
typedef size_t (FASTPNGLIB_CALLBACK *FASTPNGLIB_FILE_READCALLBACK) (void* ptr, size_t size, size_t n, FILE* stream);
typedef size_t (FASTPNGLIB_CALLBACK *FASTPNGLIB_FILE_WRITECALLBACK) (const void* ptr, size_t size, size_t n, FILE* stream);

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

typedef void (FASTPNGLIB_CALLBACK *FASTPNGLIB_SETFILESYSTEM) (FASTPNGLIB_FILE_OPENCALLBACK fileopen,FASTPNGLIB_FILE_CLOSECALLBACK fileclose,FASTPNGLIB_FILE_READCALLBACK fileread,FASTPNGLIB_FILE_WRITECALLBACK filewrite,FASTPNGLIB_FILE_TELLCALLBACK filetell,FASTPNGLIB_FILE_SEEKCALLBACK fileseek);
typedef void (FASTPNGLIB_CALLBACK *FASTPNGLIB_INIT) (void);
typedef PNG* (FASTPNGLIB_CALLBACK *FASTPNGLIB_LOADPNGDATA) (unsigned char *buffer,int size);
typedef PNG* (FASTPNGLIB_CALLBACK *FASTPNGLIB_LOADPNG) (char *filename);
typedef void (FASTPNGLIB_CALLBACK *FASTPNGLIB_CLOSE) (PNG* pngfile);


extern FASTPNGLIB_SETFILESYSTEM fastpnglib_setfilesystem;
extern FASTPNGLIB_LOADPNGDATA loadpngdata;
extern FASTPNGLIB_LOADPNG loadpng;
extern FASTPNGLIB_CLOSE freepng;


void fastpnglib_init(void);
void fastpnglib_uninit(void);


#ifdef __cplusplus
}
#endif

#pragma pack(pop)


class TPNGObject : public TGraphicObject
{
	public:
		// class constructor
		TPNGObject();
		// class destructor
		~TPNGObject();
};

#endif // PNG_H
