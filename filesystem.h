// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <dlltype.h>
#include "cimp.h"

#define FEGUI_STDCALL
#define FEGUI_CALLBACK FEGUI_STDCALL

typedef FILE* (FEGUI_CALLBACK *FEGUI_FILE_OPENCALLBACK) (const char* filename, const char* mode);
typedef int (FEGUI_CALLBACK *FEGUI_FILE_CLOSECALLBACK) (FILE* stream);
typedef long (FEGUI_CALLBACK *FEGUI_FILE_TELLCALLBACK) (FILE* stream);
typedef int (FEGUI_CALLBACK *FEGUI_FILE_SEEKCALLBACK) (FILE* stream, long offset, int whence);
typedef size_t (FEGUI_CALLBACK *FEGUI_FILE_READCALLBACK) (void* ptr, size_t size, size_t n, FILE* stream);
typedef size_t (FEGUI_CALLBACK *FEGUI_FILE_WRITECALLBACK) (const void* ptr, size_t size, size_t n, FILE* stream);

#ifdef _FEGUI
#define FEGUIFUNCTION DLLEXPORT
#else
#define FEGUIFUNCTION
#endif

//#ifndef _FEGUI

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

//#endif

extern FEGUI_FILE_OPENCALLBACK f_open;
extern FEGUI_FILE_CLOSECALLBACK f_close;
extern FEGUI_FILE_READCALLBACK f_read;
extern FEGUI_FILE_WRITECALLBACK f_write;
extern FEGUI_FILE_TELLCALLBACK f_tell;
extern FEGUI_FILE_SEEKCALLBACK f_seek;

FEGUIFUNCTION void fegui_setfilesystem(FEGUI_FILE_OPENCALLBACK fileopen,FEGUI_FILE_CLOSECALLBACK fileclose,FEGUI_FILE_READCALLBACK fileread,FEGUI_FILE_WRITECALLBACK filewrite,FEGUI_FILE_TELLCALLBACK filetell,FEGUI_FILE_SEEKCALLBACK fileseek);


//#ifndef _FEGUI

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

//#endif

#endif // FILESYSTEM_H



