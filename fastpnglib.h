//---------------------------------------------------------------------------
// Fast Portable Network Graphics Library
// by Mario Freire
// Version 1.0
// Copyright (C) 2011 DSP Interactive.
//---------------------------------------------------------------------------
#ifndef _FASTPNGLIB_H_
#define _FASTPNGLIB_H_

#include "dlltype.h"

typedef struct png
{
  int width;
  int height;
  unsigned char* pixels;
} PNG;


#define FASTPNGLIB_STDCALL _stdcall
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

FASTPNGLIB_SETFILESYSTEM fastpnglib_setfilesystem;
FASTPNGLIB_LOADPNGDATA loadpngdata;
FASTPNGLIB_LOADPNG loadpng;
FASTPNGLIB_CLOSE freepng;

HINSTANCE fastpnglibhinst;

void fastpnglib_init(void)
{
FASTPNGLIB_INIT fpnginit;

fastpnglibhinst = LoadLibrary("FASTPNGLIB.DLL");
        if(!fastpnglibhinst){
            MessageBox(NULL,"This application has failed to start because FASTPNGLIB.DLL was not found. Re-installing the application may fix this problem.","Unable To Locate Component",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);
            exit(0);
            return;
        }
 
fpnginit = (FASTPNGLIB_INIT)GetProcAddress(fastpnglibhinst, "_fastpnglib_init");
fastpnglib_setfilesystem = (FASTPNGLIB_SETFILESYSTEM)GetProcAddress(fastpnglibhinst, "_fastpnglib_setfilesystem");
loadpngdata = (FASTPNGLIB_LOADPNGDATA)GetProcAddress(fastpnglibhinst, "_loadpngdata");
loadpng = (FASTPNGLIB_LOADPNG)GetProcAddress(fastpnglibhinst, "_loadpng");
freepng = (FASTPNGLIB_CLOSE)GetProcAddress(fastpnglibhinst, "_closepng");
fpnginit();
fpnginit = NULL;
}

void fastpnglib_uninit(void)
{
 fastpnglib_setfilesystem = NULL;
 loadpngdata = NULL;
 loadpng = NULL;
 freepng = NULL;
 FreeLibrary(fastpnglibhinst);
}

/*
DLLIMPORT void fastpnglib_setfilesystem(FASTPNGLIB_FILE_OPENCALLBACK fileopen,FASTPNGLIB_FILE_CLOSECALLBACK fileclose,FASTPNGLIB_FILE_READCALLBACK fileread,FASTPNGLIB_FILE_WRITECALLBACK filewrite,FASTPNGLIB_FILE_TELLCALLBACK filetell,FASTPNGLIB_FILE_SEEKCALLBACK fileseek);
DLLIMPORT void fastpnglib_init(void);
DLLIMPORT PNG* loadpngdata(unsigned char *buffer,int size);
DLLIMPORT PNG* loadpng(char *filename);
DLLIMPORT void closepng(PNG* pngfile);
*/
#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // _FASTPNGLIB_H_
//---------------------------------------------------------------------------

